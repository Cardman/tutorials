package com.blog.example.FileUpload.Save.component;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import org.springframework.stereotype.Component;
import org.springframework.context.annotation.Scope;
import org.springframework.context.annotation.ScopedProxyMode;

//@Component
//@Scope(value = "session",proxyMode = ScopedProxyMode.TARGET_CLASS)
public class Count{

    List<String> files = new ArrayList<String>();
	
	public List<String> getFiles(){
		return files;
	}
}