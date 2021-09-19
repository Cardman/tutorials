package code;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.reactive.function.client.WebClient;
import reactor.core.publisher.Mono;

@RestController
@RequestMapping({"/api"})
public class SecController {

    private Logger logger = LoggerFactory.getLogger(SecController.class);
    private WebClient webClient;

    @Autowired
    public SecController(WebClient webClient) {
        this.webClient = webClient;
    }

    @GetMapping(path = {"/{oper}/{id}/{id2}"})
    public Integer oper(@PathVariable("oper")int oper,@PathVariable("id") int id,@PathVariable("id2") int id2){
        logger.info("{} caller => {}, {}", oper, id, id2);
        return webClient
                .get()
                .uri("api/" + oper + "/" + id + "/" + id2)
                .retrieve()
                .bodyToMono(int.class)
                .block();
    }
}
