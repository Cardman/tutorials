package gltuto.shaders;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import com.jogamp.opengl.GL2;

public final class MyShadersUtil {

	private MyShadersUtil() {
	}

	// Pour plus de simplicité, j'ajoute une fonction qui vérifie la compilation des shaders
    static boolean checkShaderCompilation(GL2 _gl, int _shaderID) {
        int[] compilationStatus_ = new int[]{0};

        // Verification de la compialtion pour le vertex shader
        _gl.glGetShaderiv(_shaderID, GL2.GL_COMPILE_STATUS, compilationStatus_, 0);
        if ( compilationStatus_[0] == 0) {
            // Nous savons que la compilation a échoué, donc nous devons savoir pourquoi
            // Nous devons récupéré la taille du log
            int[] logLength_ = new int[]{0};

            _gl.glGetShaderiv(_shaderID, GL2.GL_INFO_LOG_LENGTH, logLength_, 0);

            // Maintenant que nous avons la taille, nous pouvons alloué la mémoire suffisante pour ce log
            byte[] log_ = new byte[logLength_[0]-1];

            _gl.glGetShaderInfoLog(_shaderID, log_.length, null, 0, log_, 0);

            // On peut afficher le message
            System.out.println("Erreur de compilation:\n"+new String(log_));

            // Et on n'oublie pas de libéré la mémoire
            //            free(log);

            return false;
        }

        return true; // Pas d'erreur
    }

	/**
    Load a text file and return it as a String.
	 */
	static String loadFile(String _filename) {
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
}
