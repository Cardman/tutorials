package code;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping({"/api"})
public class Controller {

    private Logger logger = LoggerFactory.getLogger(Controller.class);
    @Autowired
    private UsageInt usageInt;
    @GetMapping(path = {"/{oper}/{id}/{id2}"})
    public int oper(@PathVariable("oper")int oper,@PathVariable("id") int id,@PathVariable("id2") int id2){
        logger.info("{} callee => {}, {}", oper, id, id2);
        return usageInt.oper(oper,id,id2);
    }
}
