package ips;


import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@ComponentScan(basePackages = {"ips"})
public class MainClass{

	public static void main(String[] args) {
		SpringApplication.run(MainClass.class, args);
	}
}