package com.yamicode.socket.rest;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;
import java.util.Map;

@RestController
@RequestMapping(value = "/api/socket")
@CrossOrigin("*")
public class SocketRest {
    @Autowired

    private SimpMessagingTemplate simpMessagingTemplate;

    @RequestMapping(method = RequestMethod.GET,value = "/send/general1")
    public ResponseEntity<?> sendMessage(){
        Thread th = new Thread(() -> {
            this.simpMessagingTemplate.convertAndSend("/socket-publisher","{1,2}");
        });
        th.start();
        try {
            th.join();
        } catch (Exception e) {
            return new ResponseEntity<>(new HttpHeaders(), HttpStatus.BAD_REQUEST);
        }
        return new ResponseEntity<>("GOOD", new HttpHeaders(), HttpStatus.OK);
    }

    @RequestMapping(method = RequestMethod.GET,value = "/send/general3")
    public ResponseEntity<?> sendMessage1(){
        this.simpMessagingTemplate.convertAndSend("/socket-publisher","{1,2}");
        return new ResponseEntity<>("GOOD", new HttpHeaders(), HttpStatus.OK);
    }

    @RequestMapping(method = RequestMethod.POST,value = "/send/general2")
    public ResponseEntity<?> sendMessage(@RequestBody  Map<String, String> message){
        Thread th = new Thread(() -> {
            if(message.containsKey("message")){
                if(message.containsKey("toId") && message.get("toId")!=null && !message.get("toId").equals("")){
                    this.simpMessagingTemplate.convertAndSend("/socket-publisher/"+message.get("toId"),message);
                    this.simpMessagingTemplate.convertAndSend("/socket-publisher/"+message.get("fromId"),message);
                }else{
                    this.simpMessagingTemplate.convertAndSend("/socket-publisher",message);
                }
            }
        });
        th.start();
        try {
            th.join();
        } catch (Exception e) {
            return new ResponseEntity<>(new HttpHeaders(), HttpStatus.BAD_REQUEST);
        }
        if(message.containsKey("message")){
            return new ResponseEntity<>(message, new HttpHeaders(), HttpStatus.OK);
        }
        return new ResponseEntity<>(new HttpHeaders(), HttpStatus.BAD_REQUEST);
    }

    @MessageMapping("/send/message")
    public Map<String, String> broadcastNotification(String message){
        ObjectMapper mapper = new ObjectMapper();
        Map<String, String> messageConverted = null;
        try {
            messageConverted = mapper.readValue(message, Map.class);
        } catch (IOException e) {
            messageConverted = null;
        }
        if(messageConverted!=null){
            if(messageConverted.containsKey("toId") && messageConverted.get("toId")!=null && !messageConverted.get("toId").equals("")){
                this.simpMessagingTemplate.convertAndSend("/socket-publisher/"+messageConverted.get("toId"),messageConverted);
                this.simpMessagingTemplate.convertAndSend("/socket-publisher/"+messageConverted.get("fromId"),message);
            }else{
                this.simpMessagingTemplate.convertAndSend("/socket-publisher",messageConverted);
            }
        }
        return messageConverted;
    }

}
