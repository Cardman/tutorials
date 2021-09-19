package code;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.*;

@Service
public class Usage implements UsageInt{

    private List<IntBean> opers;

    private Map<String,IntBean> opersMap;

	@Autowired
	public Usage(List<IntBean> opers,Map<String,IntBean> opersMap) {
    	this.opers = opers;
    	this.opersMap = opersMap;
	}
	public int oper(int key,int a, int b){
		return opers.get(key).oper(a, b);
	}

	public int oper(String key,int a, int b){
		return opersMap.get(key).oper(a, b);
	}
	public int oper(int key,int b){
		return opers.get(key).oper(b);
	}

	public int oper(String key,int b){
		return opersMap.get(key).oper(b);
	}
}