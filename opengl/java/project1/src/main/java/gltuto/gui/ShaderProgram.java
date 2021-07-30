package gltuto.gui;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GL3;

public final class ShaderProgram {
    // OpenGL handle that will point to the executable shader program
    // that can later be used for rendering
    private int programId;
 
    private GL2 gl;

    public ShaderProgram(GL2 _gl) {
        gl = _gl;
    }

    public void init(String _vertexShaderFilename, String _fragmentShaderFilename) {
        // create the shader program. If OK, create vertex and fragment shaders
        programId = gl.glCreateProgram();
 
        // load and compile the two shaders
        int vertShader_ = loadAndCompileShader(_vertexShaderFilename, GL3.GL_VERTEX_SHADER);
        int fragShader_ = loadAndCompileShader(_fragmentShaderFilename, GL3.GL_FRAGMENT_SHADER);
 
        // attach the compiled shaders to the program
        gl.glAttachShader(programId, vertShader_);
        gl.glAttachShader(programId, fragShader_);
 
        // now link the program
        gl.glLinkProgram(programId);
 
        int[] successTest_ = new int[] {0};
        gl.glGetProgramiv(programId, GL3.GL_LINK_STATUS, successTest_, 0);
        // validate linking
//        if (gl.glGetProgram(programId, GL3.GL_LINK_STATUS) == GL11.GL_FALSE) 
//        {
//            throw new RuntimeException("could not link shader. Reason: " + gl.glGetProgramInfoLog(programId, 1000));
//        }
        if (successTest_[0] == 0)  {
            System.out.println("%");
//            throw new RuntimeException("could not link shader. Reason: " + gl.glGetProgramInfoLog(programId, 1000));
        }
 
        // perform general validation that the program is usable
        gl.glValidateProgram(programId);
 
        successTest_ = new int[1];
        gl.glGetProgramiv(programId, GL3.GL_VALIDATE_STATUS, successTest_, 0);
//        if (gl.glGetProgram(programId, GL3.GL_VALIDATE_STATUS) == GL11.GL_FALSE)
//        {
//            throw new RuntimeException("could not validate shader. Reason: " + gl.glGetProgramInfoLog(programId, 1000));            
//        }
        if (successTest_[0] == 0) {
            System.out.println("%");
//            throw new RuntimeException("could not validate shader. Reason: " + gl.glGetProgramInfoLog(programId, 1000));            
        }
    }
 
   /*
     With the exception of syntax, setting up vertex and fragment shaders
     is the same.
     @param the name and path to the vertex shader
    */
    private int loadAndCompileShader(String _filename, int _shaderType) {
        //vertShader will be non zero if succefully created
        int handle_ = gl.glCreateShader(_shaderType);
 
        if( handle_ == 0 ) {
            System.out.println("%");
//            throw new RuntimeException("could not created shader of type "+shaderType+" for file "+filename+". "+ gl.glGetProgramInfoLog(programId, 1000));
        }
 
        // load code from file into String
        String code_ = loadFile(_filename);
 
        // upload code to OpenGL and associate code with shader
        gl.glShaderSource(handle_, 1, new String[] {code_}, null);
//        gl.glShaderSource(handle, code);
 
        // compile source code into binary
        gl.glCompileShader(handle_);
        int[] successTest_ = new int[] {0};
 
        // acquire compilation status
//        int shaderStatus = gl.glGetShader(handle, GL2.GL_COMPILE_STATUS);
        gl.glGetShaderiv(handle_, GL3.GL_COMPILE_STATUS, successTest_, 0);
 
        // check whether compilation was successful
//        if( shaderStatus == GL11.GL_FALSE)
//        {
//            throw new IllegalStateException("compilation error for shader ["+filename+"]. Reason: " + gl.glGetShaderInfoLog(handle, 1000));
//        }
        if(successTest_[0] == 0) {
            System.out.println("%");
//            System.out.println("compilation error for shader ["+filename+"]. Reason: " + gl.glGetShaderInfoLog(handle, 1000));
        }
 
        return handle_;
    }
 
    /**
      Load a text file and return it as a String.
     */
    private String loadFile(String _filename) {
        StringBuilder vertexCode_ = new StringBuilder();
        String line_ = null;
        try {
            InputStream is_ = ClassLoader.getSystemResourceAsStream(_filename);
            BufferedReader reader_ = new BufferedReader(new InputStreamReader(is_));
            while( (line_ = reader_.readLine()) !=null ) {
                vertexCode_.append(line_);
                vertexCode_.append('\n');
            }
        } catch(Exception _0) {
            throw new IllegalArgumentException("unable to load shader from file ["+_filename+"]", _0);
        }
 
        return vertexCode_.toString();
    }
 
 
    public int getProgramId() {
        return programId;
    }    
}
