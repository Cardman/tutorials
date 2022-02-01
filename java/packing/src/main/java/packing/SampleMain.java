package packing;
import code.vi.prot.impl.*;
import code.gui.initialize.*;
import code.gui.*;
import code.gui.images.*;
import code.util.*;
import code.util.core.*;
import code.threads.*;
import code.expressionlanguage.filenames.*;
import code.stream.core.*;
import code.stream.*;
import code.expressionlanguage.*;
import code.expressionlanguage.structs.*;
import code.expressionlanguage.utilimpl.*;
import code.expressionlanguage.gui.unit.*;
import code.expressionlanguage.utilcompo.*;
import code.vi.prot.impl.*;
import java.io.*;

public class SampleMain{
	public static void main(String...args){
		System.setProperty("java.awt.headless", "true");
		final AbstractFileCoreStream str = new AbstractFileCoreStream() {

			@Override
			public AbstractListRoot newFileList() {
				return null;
			}

			@Override
			public AbstractFile newFile(String _fileName) {
				return new DefaultFile(_fileName);
			}
		};
		AbstractBinFactory bin = new AbstractBinFactory() {
			@Override
			public AbstractBinStreamIn buildIn(final String _filePath) {
				return new AbstractBinStreamIn() {
					private InputStream reader;
					 {
						reader = tryCreateFileInputStream(_filePath);
					}

					public InputStream tryCreateFileInputStream(String _file) {
						try {
							return new FileInputStream(StringUtil.nullToEmpty(_file));
						} catch (Exception e) {
							return null;
						}
					}
					@Override
					public boolean close() {
						return StreamCoreUtil.close(reader);
					}

					@Override
					public int read(byte[] _array, int _off, int _len) {
						try {
							return reader.read(_array, _off, _len);
						} catch (Exception e) {
							return -2;
						}
					}
				};
			}

			@Override
			public boolean writeFile(String _file, byte[] _content) {
				return write(_content, tryCreateFileOutputStream(_file));
			}

			public OutputStream tryCreateFileOutputStream(String _file) {
				try {
					return new FileOutputStream(StringUtil.nullToEmpty(_file));
				} catch (Exception e) {
					return null;
				}
			}
			private boolean write(byte[] _content, OutputStream _fos) {
				OutputStream w_ = write2(_content, _fos);
				return StreamCoreUtil.close(w_);
			}

			private OutputStream write2(byte[] _content, OutputStream _buff) {
				try {
					_buff.write(_content);
					return _buff;
				} catch (Exception e) {
					return _buff;
				}

			}
		};
		final TechStreams tech = new TechStreams(new DefBinFact(bin),null,new DefZipFact(new DefZipFactory()));
		
		final LightProgramInfos lg = new LightProgramInfos(new AdvGraphicStringListGenerator(), new AdvGraphicComboBoxGenerator()){
			public AbstractFileCoreStream getFileCoreStream() {
				return str;
			}
			public TechStreams getStreams() {
				return tech;
			}
		};
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
		final StringBuilder conf = new StringBuilder("arc\nfr\ncover=");
		final StringMap<byte[]> src = new StringMap<byte[]>();
		src.addEntry("src/file.txt",StringUtil.encode("classe pq.Mille{@Test vide meth(){}}"));
		final StringMap<byte[]> files = new StringMap<byte[]>();
		TestableFrame test = new TestableFrame(){
			byte[] confFile;
			public boolean ok(String _file){
				return true;
			}
			public AbstractInterceptor getIntercept() {
				return lg.getInterceptor();
			}
			public String getTxtConf() {
				String trim_ = conf.toString().trim();
				confFile = StringUtil.encode(trim_);
				return trim_;
			}
			public void showProgress(ContextEl _ctx, Struct _infos, Struct _doneTests, Struct _method, Struct _count, LgNamesWithNewAliases _evolved){
				
			}
			public void finish(Struct _infos, LgNamesWithNewAliases _evolved){
				
			}
			public void setResults(ContextEl _ctx, Argument _res, LgNamesWithNewAliases _evolved){
			}
			public FileInfos getInfos() {
				AbstractNameValidating validator_ = lg.getValidator();
				return FileInfos.buildMemoryFromFile(lg.getGenerator(),
						validator_,new AbstractIssuer(){
							public void log(String _info){
								System.out.println(_info);
							}
						}, new MemInputFiles(confFile, lg.getStreams().getZipFact().zipBinFiles(map(src)), lg.getStreams().getZipFact().zipBinFiles(map(files))), lg.getStreams().getZipFact(), lg.getThreadFactory());
			}
			public AbstractThreadFactory getThreadFactory() {
				return lg.getThreadFactory();
			}
		};
		String txt_ = test.getTxtConf();
		FileInfos infos = test.getInfos();
		RunningTest r_ = RunningTest.newFromContent(txt_, new ProgressingTestsImpl(test,lg.getStreams(),lg.getFileCoreStream()),
                infos);
		AbstractThread th_ = lg.getThreadFactory().newThread(r_);
        th_.start();
        th_.join();
	}
	private static StringMap<ContentTime> map(StringMap<byte[]> _files){
		StringMap<ContentTime> files_ = new StringMap<ContentTime>();
		int fileLength_ = _files.size();
		for (int j = 0; j < fileLength_; j++) {
			files_.addEntry(_files.getKey(j),new ContentTime(_files.getValue(j),System.currentTimeMillis()));
		}
		return files_;
	}
}