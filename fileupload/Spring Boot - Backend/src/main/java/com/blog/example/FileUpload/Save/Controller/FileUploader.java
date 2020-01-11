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


@CrossOrigin(origins = "http://localhost:4200")
@Controller
public class FileUploader {

	private AtomicLong fileCount = new AtomicLong(0);
	private ConcurrentHashMap<Long,ArrayList<String>> filesMap = new ConcurrentHashMap<Long,ArrayList<String>>();

	@PostMapping("/savefile")
	public ResponseEntity<String> handleFileUpload(@RequestParam("file") MultipartFile file,@RequestParam("file2") MultipartFile file2,@RequestParam("s2") String s) {
		try {
			long v = fileCount.incrementAndGet();
			ArrayList<String> files = new ArrayList<String>();
			files.add(file.getOriginalFilename());
			files.add(file2.getOriginalFilename());
			filesMap.put(v,files);

			return ResponseEntity.status(HttpStatus.OK).body(v+"");
		} catch (Exception e) {
			return ResponseEntity.status(HttpStatus.EXPECTATION_FAILED).body("");
		}
	}

	@PostMapping(value = "/downloadlist")
    public ResponseEntity<byte[]> getSteamingFile(@RequestParam("s2") String s) throws IOException {

/*ClassPathResource res = new ClassPathResource("resources_lg/threads/runnable.txt");
BufferedReader reader = new BufferedReader(
      new InputStreamReader(res.getInputStream()));*/

ArrayList<String> ls = filesMap.remove(Long.parseLong(s));
String employees = ls.stream().collect(Collectors.joining("\n"));
byte[] isr = employees.getBytes();
        return ResponseEntity.ok()
		.header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + "files.txt")
		.contentType(MediaType.APPLICATION_OCTET_STREAM)
		.body(isr);
    }
	
	@PostMapping(value = "/clearList")
    public ResponseEntity<String> clearList(@RequestParam("s2") String s) throws IOException {

filesMap.remove(Long.parseLong(s));

        return ResponseEntity.ok("");
    }
}
