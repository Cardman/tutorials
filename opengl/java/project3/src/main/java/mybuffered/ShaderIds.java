package mybuffered;

public final class ShaderIds {

    private final int vertexId;

    private final int fragmentId;

    private final int programId;

	public ShaderIds(int _vertexId, int _fragmentId, int _programId) {
		vertexId = _vertexId;
		fragmentId = _fragmentId;
		programId = _programId;
	}

	public int getVertexId() {
		return vertexId;
	}

	public int getFragmentId() {
		return fragmentId;
	}

	public int getProgramId() {
		return programId;
	}
}
