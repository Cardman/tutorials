package ips;

import java.util.concurrent.atomic.*;
import code.expressionlanguage.common.*;
import org.springframework.cache.annotation.*;
import org.springframework.stereotype.*;

@EnableCaching
@Service
public class CacheSample{
	private AtomicLong count = new AtomicLong(0);
	private AtomicLong count2 = new AtomicLong(0);
	private AtomicLong count3 = new AtomicLong(0);
	@Cacheable(value = "first", key = "#cacheKey")
	public long addSingleCacheValue(String cacheKey) {
		count.incrementAndGet();
		long sum = 0L;
		for (char c: cacheKey.toCharArray()){
			count.incrementAndGet();
			int type = StringDataUtil.getCustomType(c);
			if (type == 1){
				sum += c * 5;
				continue;
			}
			if (type == 2){
				sum += c * 2;
				continue;
			}
			if (type == 3 || type == 4){
				sum += c + 1;
				continue;
			}
			if (type == 5 || type == 6){
				sum += c * 2 + 1;
				continue;
			}
			if (type == 7 || type == 8 || type == 9){
				sum += c * 3 + 2;
				continue;
			}
			if (type == 10){
				sum += (c-'0'+1) * (c*3-'0'+2);
				continue;
			}
			if (type == 11){
				sum += c-'0'-15*16;
				continue;
			}
			if (type >= 12 && type <= 15){
				sum += 15*c-15*16*1500;
				continue;
			}
			if (type >= 16 && type <= 30){
				sum += c * c * c /(c * c + 1);
				continue;
			}
			if (type == 31){
				sum += c * c - c * 15000;
				continue;
			}
			if (type == 32){
				sum += c * c / 4 - 1235;
				continue;
			}
			sum += c * c * c - c * c * 5 + 12 * c -c;
		}
		return sum;
	}
	@CacheEvict(value = "first", key = "#cacheKey")
	public int evictSingleCacheValue(String cacheKey) {
		count.set(0);
		return cacheKey.length();
	}
	@Cacheable(value = "second")
	public long addSingleCacheValue(String cacheKey, int counter) {
		count2.incrementAndGet();
		long sum = 0L;
		for (char c: cacheKey.toCharArray()){
			count2.incrementAndGet();
			int type = StringDataUtil.getCustomType(c);
			if (type == 1){
				sum += c * 2;
				continue;
			}
			if (type == 2){
				sum += c * 5;
				continue;
			}
			if (type == 3 || type == 4){
				sum += c + 1;
				continue;
			}
			if (type == 5 || type == 6){
				sum += c * 4 + 1;
				continue;
			}
			if (type == 7 || type == 8 || type == 9){
				sum += c * 2 + 3;
				continue;
			}
			if (type == 10){
				sum += (c-'0'+1) * (c*3-'0'+2);
				continue;
			}
			if (type == 11){
				sum += c-'0'-15*16;
				continue;
			}
			if (type >= 12 && type <= 15){
				sum += 15*c-15*16*1500;
				continue;
			}
			if (type >= 16 && type <= 30){
				sum += c * c * c /(c * c + 1);
				continue;
			}
			if (type == 31){
				sum += c * c - c * 15000;
				continue;
			}
			if (type == 32){
				sum += c * c / 4 - 1235;
				continue;
			}
			sum += c * c * c - c * c * 5 + 12 * c -c;
		}
		return sum * counter;
	}
	@CacheEvict(value = "second")
	public int evictSingleCacheValue(String cacheKey, int counter) {
		count2.set(0);
		return cacheKey.length();
	}
	@Cacheable(value = "third", key = "#cacheKey+\"_\"+#counter")
	public long addSingleCacheValue1(String cacheKey, int counter) {
		count3.incrementAndGet();
		long sum = 0L;
		for (char c: cacheKey.toCharArray()){
			count3.incrementAndGet();
			int type = StringDataUtil.getCustomType(c);
			if (type == 1){
				sum += c * 2 * c;
				continue;
			}
			if (type == 2){
				sum += c * 5 * c;
				continue;
			}
			if (type == 3 || type == 4){
				sum += c + 1;
				continue;
			}
			if (type == 5 || type == 6){
				sum += c * 4 + 1;
				continue;
			}
			if (type == 7 || type == 8 || type == 9){
				sum += c * 2 + 3;
				continue;
			}
			if (type == 10){
				sum += (c-'0'+1) * (c*3-'0'+2);
				continue;
			}
			if (type == 11){
				sum += c-'0'-15*16;
				continue;
			}
			if (type >= 12 && type <= 15){
				sum += 15*c-15*16*1500;
				continue;
			}
			if (type >= 16 && type <= 30){
				sum += c * c * c /(c * c + 1);
				continue;
			}
			if (type == 31){
				sum += c * c - c * 15000;
				continue;
			}
			if (type == 32){
				sum += c * c / 4 - 1235;
				continue;
			}
			sum += c * c * c - c * c * 5 + 12 * c -c;
		}
		return sum * counter;
	}
	@CacheEvict(value = "third", key = "#cacheKey+\"_\"+#counter")
	public int evictSingleCacheValue1(String cacheKey, int counter) {
		count3.set(0);
		return cacheKey.length();
	}
	public long get(){
		return count.get();
	}
	public long get2(){
		return count2.get();
	}
	public long get3(){
		return count3.get();
	}
}