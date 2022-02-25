package coq;

import java.util.*;

public class Delimiters {
	public static final int TYPE_SIN_CMT = 1;
	public static final int TYPE_MUL_CMT = 2;
	public static final int TYPE_CHAR = 3;
	public static final int TYPE_STRING = 4;
	private Delimiters(){}
	public static List<SegmentPart> dels(String input) {
		List<SegmentPart> parts = new ArrayList<SegmentPart>();
		boolean cstChar = false;
		boolean cstString = false;
		boolean singleCmt = false;
		boolean multCmt = false;
		int len = input.length();
		int i = 0;
		int begin = 0;
		while (i < len){
			char ch = input.charAt(i);
			if (singleCmt){
				if (ch == '\n') {
					singleCmt = false;
					SegmentPart seg = new SegmentPart();
					seg.begin = begin;
					seg.end = i+1;
					seg.type = TYPE_SIN_CMT;
					seg.green=255;
					seg.size=12;
					parts.add(seg);
				}
				i++;
				continue;
			}
			if (multCmt){
				if (ch == '*' && i + 1 < len && input.charAt(i+1) == '\\') {
					multCmt = false;
					SegmentPart seg = new SegmentPart();
					seg.begin = begin;
					seg.end = i+2;
					seg.type = TYPE_MUL_CMT;
					seg.green=255;
					seg.size=12;
					parts.add(seg);
					i++;
					i++;
					continue;
				}
				i++;
				continue;
			}
			if (cstChar){
				if (ch == '\\') {
					i++;
					i++;
					continue;
				}
				if (ch == '\'') {
					SegmentPart seg = new SegmentPart();
					seg.begin = begin;
					seg.end = i+1;
					seg.type = TYPE_CHAR;
					seg.blue=255;
					seg.size=12;
					parts.add(seg);
					i++;
					cstChar = false;
					continue;
				}
				i++;
				continue;
			}
			if (cstString){
				if (ch == '\\') {
					i++;
					i++;
					continue;
				}
				if (ch == '"') {
					SegmentPart seg = new SegmentPart();
					seg.begin = begin;
					seg.end = i+1;
					seg.type = TYPE_STRING;
					seg.blue=255;
					seg.size=12;
					parts.add(seg);
					i++;
					cstString = false;
					continue;
				}
				i++;
				continue;
			}
			if (ch == '\\' && i + 1 < len){
				if (input.charAt(i+1) == '\\'){
					begin = i;
					i++;
					i++;
					singleCmt = true;
					continue;
				}
				if (input.charAt(i+1) == '*'){
					begin = i;
					i++;
					i++;
					multCmt = true;
					continue;
				}
			}
			if (ch == '"'){
				cstString = true;
				begin = i;
			}
			if (ch == '\''){
				cstChar = true;
				begin = i;
			}
			i++;
		}
		if (singleCmt){
			SegmentPart seg = new SegmentPart();
			seg.begin = begin;
			seg.end = len;
			seg.type = TYPE_SIN_CMT;
			seg.green=255;
			seg.size=12;
			parts.add(seg);
		}
		if (multCmt){
			SegmentPart seg = new SegmentPart();
			seg.begin = begin;
			seg.end = len;
			seg.type = TYPE_MUL_CMT;
			seg.green=255;
			seg.size=12;
			parts.add(seg);
		}
		if (cstChar){
			SegmentPart seg = new SegmentPart();
			seg.begin = begin;
			seg.end = len;
			seg.type = TYPE_CHAR;
			seg.blue=255;
			seg.size=12;
			parts.add(seg);
		}
		if (cstString){
			SegmentPart seg = new SegmentPart();
			seg.begin = begin;
			seg.end = len;
			seg.type = TYPE_STRING;
			seg.blue=255;
			seg.size=12;
			parts.add(seg);
		}
		return parts;
	}

}