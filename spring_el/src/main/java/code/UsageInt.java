package code;

import java.util.List;
import java.util.Set;

public interface UsageInt {

    int oper(int key,int a, int b);
    int oper(String key,int a, int b);

    int oper(int key,int a);
    int oper(String key,int a);

    List<IntBean> countFilterList();
    Set<String> countFilter();
}