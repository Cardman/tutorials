package sample;

import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

public class AnswerGetValue implements Answer<String> {
    private final Mocked mocked;

    public AnswerGetValue(Mocked m) {
        this.mocked = m;
    }

    @Override
    public String answer(InvocationOnMock invocationOnMock) {
        return mocked.getValue();
    }
}
