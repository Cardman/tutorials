package code.mock;

public class MockInput extends MockCustComponent{
    private boolean enabled;

    public boolean isEnabled() {
        return enabled;
    }

    public void setEnabled(boolean _en) {
        this.enabled = _en;
    }

    @Override
    public boolean isAccessible() {
        if (!enabled) {
            return false;
        }
        return super.isAccessible();
    }
}
