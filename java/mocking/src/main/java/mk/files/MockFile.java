package mk.files;

import java.io.File;

public class MockFile{
	private final File file;
	public MockFile(File file){
		this.file = file;
	}
	
    public String getName() {
        return file.getName();
    }

    
    public String getAbsolutePath() {
        return file.getAbsolutePath();
    }

    
    public String[] list() {
        return file.list();
    }

    
    public boolean isDirectory() {
        return file.isDirectory();
    }

    
    public boolean exists() {
        return file.exists();
    }

    
    public long length() {
        return file.length();
    }

    
    public long lastModified() {
        return file.lastModified();
    }

    
    public boolean renameTo(MockFile _newFile) {
        return file.renameTo(_newFile.file);
    }

    
    public boolean delete() {
        return file.delete();
    }

    
    public String getParent() {
        return file.getParent();
    }

    
    public boolean mkdirs() {
        return file.mkdirs();
    }
}