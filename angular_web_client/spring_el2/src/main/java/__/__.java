package __;


import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@ComponentScan(basePackages = {"code"})
public class __{

	public static void main(String[] args) {
		SpringApplication.run(__.class, args);
	}
}