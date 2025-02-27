import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';

import * as Stomp from 'stompjs';
import * as SockJS from 'sockjs-client';
import { environment } from '../../../environments/environment';
import { SocketService } from '../../services/socket.service';
import { ToastrService } from 'ngx-toastr';
import { Message } from '../../model/message';
import { Subject } from 'rxjs';

@Component({
  selector: 'app-yami-code-socket',
  templateUrl: './yami-code-socket.component.html',
  styleUrls: ['./yami-code-socket.component.css']
})
export class YamiCodeSocketComponent implements OnInit {
  //serverUrl = '/socket'
  serverUrl = 'http://localhost:8080/socket/'
  isLoaded: boolean = true;
  isCustomSocketOpened = false;
  stompClient;
  form: FormGroup;
  userForm: FormGroup;
  messages: Message[] = [];
  subGlobal: Subject<any>;
  subLocal: Subject<any>;
  constructor(private socketService: SocketService, private toastr: ToastrService
  ) { }

  ngOnInit() {
    this.form = new FormGroup({
      message: new FormControl(null, [Validators.required])
    })
    this.userForm = new FormGroup({
      fromId: new FormControl(null, [Validators.required]),
      toId: new FormControl(null)
    })
  }

  sendMessageUsingSocket() {
    if (this.form.valid) {
      let message: Message = { message: this.form.value.message, fromId: this.userForm.value.fromId, toId: this.userForm.value.toId };
      this.stompClient.send("/socket-subscriber/send/message", {}, JSON.stringify(message));
    }
  }

  sendMessageUsingRest() {
    if (this.form.valid) {
      let message: Message = { message: this.form.value.message, fromId: this.userForm.value.fromId, toId: this.userForm.value.toId };
      this.socketService.post(message).subscribe(res => {
        console.log(res);
      })
    }
  }

  initializeWebSocketConnection() {
    let ws = new SockJS(this.serverUrl);
    this.stompClient = Stomp.over(ws);
    let that = this;
    this.stompClient.connect({}, function (frame) {
      that.isLoaded = true;
      that.openGlobalSocket();
	  that.openSocket();
    });
  }

  openGlobalSocket() {
    this.subGlobal = this.stompClient.subscribe("/socket-publisher", (message) => {
      this.handleResult(message);
    });
  }

  openSocket() {
    if (this.isLoaded) {
      this.isCustomSocketOpened = true;
      this.subLocal = this.stompClient.subscribe("/socket-publisher/"+this.userForm.value.fromId, (message) => {
        this.handleResult(message);
      });
    }
  }

  disconnect(){
    if (this.stompClient){
		this.stompClient.disconnect();
	}
    if (this.subLocal){
		this.subLocal.unsubscribe();
	}
	if (this.subGlobal){
		this.subGlobal.unsubscribe();
	}
	this.isCustomSocketOpened = false;
  }
  handleResult(message){
    console.log(message);
      if (message.body) {
      let messageResult: Message = JSON.parse(message.body);
      console.log(messageResult);
      this.messages.push(messageResult);
      this.toastr.success("new message recieved", "null", {
        'timeOut': 3000
      });
    }
  }

}
