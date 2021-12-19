package ips;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import org.springframework.web.context.request.*;


@RestController
@RequestMapping({"/api"})
public class IpController{
	@Autowired
	private CacheSample cacheSample;

	@GetMapping(path = {"/curip"})
    public String currentIp(){
        return ((ServletRequestAttributes)RequestContextHolder.getRequestAttributes()).getRequest().getRemoteAddr();
    }
	@GetMapping(path = {"/add"})
    public String add(@RequestParam("key") String key){
        long value = cacheSample.addSingleCacheValue(key);
        return key+":"+value+","+cacheSample.get();
    }
	@GetMapping(path = {"/remove"})
    public String remove(@RequestParam("key") String key){
        int value = cacheSample.evictSingleCacheValue(key);
        return key+":"+value+","+cacheSample.get();
    }
}