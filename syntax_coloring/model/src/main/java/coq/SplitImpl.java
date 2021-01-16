package coq;
import java.util.*;
public class SplitImpl implements Split {
	public List<SegmentPart> dels(String input){
		return Delimiters.dels(input);
	}
}