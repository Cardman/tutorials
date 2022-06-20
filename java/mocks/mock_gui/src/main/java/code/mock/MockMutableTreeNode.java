package code.mock;

import code.gui.AbstractMutableTreeNode;
import code.util.IdList;
import code.util.core.StringUtil;

public class MockMutableTreeNode implements AbstractMutableTreeNode {
    private final String userObject;
    private MockMutableTreeNode parent;
    private MockMutableTreeNode firstChild;
    private MockMutableTreeNode nextSibling;
    private boolean accessible;

    public MockMutableTreeNode(String _name) {
        userObject = StringUtil.nullToEmpty(_name);
    }

    @Override
    public int getIndex() {
        if (parent == null) {
            return -1;
        }
        return parent.children().indexOfObj(this);
    }

    @Override
    public int getAntiIndex(AbstractMutableTreeNode abstractMutableTreeNode) {
        return children().indexOfObj((MockMutableTreeNode) abstractMutableTreeNode);
    }

    @Override
    public boolean add(AbstractMutableTreeNode abstractMutableTreeNode) {
        append((MockMutableTreeNode) abstractMutableTreeNode);
        return false;
    }

    private void append(MockMutableTreeNode abstractMutableTreeNode) {
        abstractMutableTreeNode.removeFromParent();
        IdList<MockMutableTreeNode> ch_ = children();
        abstractMutableTreeNode.parent = this;
        if (ch_.isEmpty()) {
            firstChild = abstractMutableTreeNode;
        } else {
            ch_.last().nextSibling= abstractMutableTreeNode;
        }
    }

    @Override
    public int getChildCount() {
        return children().size();
    }

    @Override
    public int insert(AbstractMutableTreeNode abstractMutableTreeNode, int i) {
        abstractMutableTreeNode.removeFromParent();
        int index_ = 0;
        MockMutableTreeNode prev_ = null;
        MockMutableTreeNode curr_ = firstChild;
        while (curr_ != null) {
            if (index_ == i) {
                insert((MockMutableTreeNode) abstractMutableTreeNode, prev_, curr_);
                return i;
            }
            prev_ = curr_;
            curr_ = curr_.nextSibling;
            index_++;
        }
        if (index_ == i) {
            insert((MockMutableTreeNode) abstractMutableTreeNode, prev_, null);
            return i;
        }
        return -1;
    }

    private void insert(MockMutableTreeNode abstractMutableTreeNode, MockMutableTreeNode prev_, MockMutableTreeNode curr_) {
        if (prev_ == null) {
            abstractMutableTreeNode.nextSibling = firstChild;
            firstChild = abstractMutableTreeNode;
        } else {
            abstractMutableTreeNode.nextSibling = curr_;
            prev_.nextSibling = abstractMutableTreeNode;
        }
    }

    @Override
    public int removeAllChildren() {
        int ch_ = getChildCount();
        for (MockMutableTreeNode m: children()) {
            m.parent = null;
            m.nextSibling = null;
        }
        firstChild = null;
        return ch_;
    }

    @Override
    public AbstractMutableTreeNode getParent() {
        return parent;
    }

    @Override
    public int remove(AbstractMutableTreeNode abstractMutableTreeNode) {
        int index_ = 0;
        MockMutableTreeNode prev_ = null;
        MockMutableTreeNode curr_ = firstChild;
        while (curr_ != null) {
            if (curr_ == abstractMutableTreeNode) {
                clear(prev_, curr_);
                return index_;
            }
            prev_ = curr_;
            curr_ = curr_.nextSibling;
            index_++;
        }
        return -1;
    }

    @Override
    public AbstractMutableTreeNode remove(int i) {
        int index_ = 0;
        MockMutableTreeNode prev_ = null;
        MockMutableTreeNode curr_ = firstChild;
        while (curr_ != null) {
            if (index_ == i) {
                clear(prev_, curr_);
                return curr_;
            }
            prev_ = curr_;
            curr_ = curr_.nextSibling;
            index_++;
        }
        return null;
    }

    private void clear(MockMutableTreeNode prev_, MockMutableTreeNode curr_) {
        if (prev_ == null) {
            firstChild = curr_.nextSibling;
        } else {
            prev_.nextSibling = curr_.nextSibling;
        }
        curr_.nextSibling = null;
        curr_.parent = null;
    }

    @Override
    public AbstractMutableTreeNode getChildAt(int i) {
        IdList<MockMutableTreeNode> ch_ = children();
        if (ch_.isValidIndex(i)) {
            return ch_.get(i);
        }
        return null;
    }

    @Override
    public AbstractMutableTreeNode getPreviousSibling() {
        int index_ = getIndex();
        if (index_ < 1) {
            return null;
        }
        IdList<MockMutableTreeNode> ch_ = parent.children();
        return ch_.get(index_ - 1);
    }

    @Override
    public AbstractMutableTreeNode getNextSibling() {
        return nextSibling;
    }

    @Override
    public AbstractMutableTreeNode removeFromParent() {
        if (parent != null) {
            AbstractMutableTreeNode old_ = getParent();
            MockMutableTreeNode prev_ = (MockMutableTreeNode) getPreviousSibling();
            if (prev_ == null) {
                parent.firstChild = nextSibling;
                parent = null;
                nextSibling = null;
                return old_;
            }
            prev_.nextSibling = nextSibling;
            parent = null;
            nextSibling = null;
            return old_;
        }
        return null;
    }

    @Override
    public AbstractMutableTreeNode add(String s) {
        MockMutableTreeNode abstractMutableTreeNode = new MockMutableTreeNode(s);
        append(abstractMutableTreeNode);
        return abstractMutableTreeNode;
    }

    @Override
    public AbstractMutableTreeNode original() {
        return this;
    }

    @Override
    public String getUserObject() {
        return userObject;
    }
    private IdList<MockMutableTreeNode> children() {
        IdList<MockMutableTreeNode> ch_ = new IdList<MockMutableTreeNode>();
        MockMutableTreeNode curr_ = firstChild;
        while (curr_ != null) {
            ch_.add(curr_);
            curr_ = curr_.nextSibling;
        }
        return ch_;
    }

    public boolean isAccessible() {
        return accessible;
    }

    public void setAccessible(boolean _a) {
        this.accessible = _a;
    }
}
