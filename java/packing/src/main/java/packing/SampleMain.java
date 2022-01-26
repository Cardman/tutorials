package packing;
import code.vi.prot.impl.LigOtherProgramInfos;
import code.gui.initialize.*;
import code.gui.*;
import code.gui.images.*;
import code.util.*;

public class SampleMain{
	public static void main(String...args){
		System.setProperty("java.awt.headless", "true");
		LigOtherProgramInfos lg = new LigOtherProgramInfos();
		AbsLightFrameFactory abs = lg.getLightFrameFactory();
		AbsCompoFactory compo = lg.getCompoFactory();
		AbsOtherFrame fr = abs.newOtherFrame();
		AbsPanel view = compo.newGrid(0,10);
		CustList<AbsCustComponent> ls_ = new CustList<AbsCustComponent>();
		for (long i = 0; i < 10; i++) {
			for (long j = 0; j < 10; j++) {
				long p = 1;
				for (long k = 0; k < j; k++){
					p *= i;
				}
				AbsCustComponent c_ = compo.newPlainLabel(Long.toString(p));
				view.add(c_);
				ls_.add(c_);
			}
		}
		AbsPanel content_ = compo.newGrid(0,1);
		//AbsScrollPane scroll = compo.newAbsScrollPane(view);
		AbsScrollPane scroll = compo.newAbsScrollPane();
		scroll.setPreferredSize(new MetaDimension(64,64));
		scroll.setViewportView(view);
		content_.add(scroll);
		fr.setContentPane(content_);
		fr.pack();
		for (AbsCustComponent c: ls_){
			System.out.println(c.getXcoords()+","+c.getYcoords());
		}
		System.out.println(view.getXcoords()+","+view.getYcoords());
		scroll.setHorizontalValue(150);
		scroll.setVerticalValue(50);
		fr.pack();
		System.out.println(view.getXcoords()+","+view.getYcoords());
	}
}