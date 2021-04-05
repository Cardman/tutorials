package com.blog.example.FileUpload.Save.Controller;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import org.springframework.web.servlet.mvc.method.annotation.StreamingResponseBody;

import org.springframework.core.io.InputStreamResource;
import javax.servlet.http.HttpServletResponse;
import org.springframework.messaging.simp.SimpMessagingTemplate;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.*;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.ConcurrentHashMap;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.Collection;
import java.util.stream.Collectors;

import org.springframework.util.ResourceUtils;
import org.springframework.core.io.ClassPathResource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Scope;
import org.springframework.context.annotation.ScopedProxyMode;

import com.blog.example.FileUpload.Save.component.Count;


@Controller
public class FileUploader {

    @Autowired
    private SimpMessagingTemplate simpMessagingTemplate;

	private AtomicLong fileCount = new AtomicLong(0);
	private ConcurrentHashMap<Long,ArrayList<String>> filesMap = new ConcurrentHashMap<Long,ArrayList<String>>();

	@PostMapping("/savefile")
	public ResponseEntity<String> handleFileUpload() {
		try {
			final long v = fileCount.incrementAndGet();
			filesMap.put(v,new ArrayList<String>());
			Runnable r = () -> {
				simpMessagingTemplate.convertAndSend("/socket-publisher","begin "+v);
				while (filesMap.containsKey(v)){
					try {
						Thread.sleep(1000);
					}catch(Exception e){}
				}
				simpMessagingTemplate.convertAndSend("/socket-publisher","end "+v);
			};
			ResponseEntity<String> out = ResponseEntity.status(HttpStatus.OK).body(v+"");
			new Thread(r).start();
			return out;
		} catch (Exception e) {
			return ResponseEntity.status(HttpStatus.EXPECTATION_FAILED).body("");
		}
	}

	
	@PostMapping(value = "/clearList")
    public ResponseEntity<String> clearList(@RequestParam("s2") String s) throws IOException {

filesMap.remove(Long.parseLong(s));

        return ResponseEntity.ok("");
    }
}
