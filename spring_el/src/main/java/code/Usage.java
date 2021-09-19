package code;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import java.util.*;

@Service
public class Usage implements UsageInt{

    private final List<IntBean> opers;
    private final List<IntBean> opers2;

    private final Map<String,IntBean> opersMap;
    private final Map<String,IntBean> opersMap2;

	@Autowired
	public Usage(List<IntBean> opers,@Qualifier(Config.COLLECTIONS_BEAN) List<IntBean> opers2,Map<String,IntBean> opersMap,@Qualifier(Config.COLLECTIONS_BEAN) Map<String,IntBean> opersMap2) {
    	this.opers = opers;
    	this.opers2 = opers2;
    	this.opersMap = opersMap;
    	this.opersMap2 = opersMap2;
	}

	@Override
	public List<IntBean> countFilterList() {
		return opers2;
	}

	@Override
	public Set<String> countFilter() {
		return opersMap2.keySet();
	}

	public int oper(int key, int a, int b){
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