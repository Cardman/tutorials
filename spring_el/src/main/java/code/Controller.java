package code;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping({"/api"})
public class Controller {

    @Autowired
    private UsageInt usageInt;
    @GetMapping(path = {"/{oper}/{id}/{id2}"})
    public int oper(@PathVariable("oper")int oper,@PathVariable("id") int id,@PathVariable("id2") int id2){
        return usageInt.oper(oper,id,id2);
    }
}
