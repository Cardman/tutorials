package sample;

import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

public class AnswerSetValue implements Answer<String> {
    private final Mocked mocked;
    private String ans;

    public AnswerSetValue(Mocked m) {
        this.mocked = m;
    }

    @Override
    public String answer(InvocationOnMock invocationOnMock) {
        String argument = (String) invocationOnMock.getArguments()[0];
        ans = argument;
        mocked.setValue(argument);
        return "";
    }

    public String getAns() {
        return ans;
    }
}
