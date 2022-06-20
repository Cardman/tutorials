package code.mock;

import code.gui.AbsCustComponent;
import code.gui.AbsShortListTree;
import code.gui.AbsTreeGui;
import code.gui.AbstractMutableTreeNode;
import code.util.CustList;
import code.util.IdList;

public class MockTreeGui extends MockCustComponent implements AbsTreeGui {
    private final MockTreeComponent tree;
    private AbstractMutableTreeNode selected;
    private final IdList<AbsShortListTree> list = new IdList<AbsShortListTree>();

    public MockTreeGui(AbstractMutableTreeNode _t) {
        selected = _t;
        tree = new MockTreeComponent();
    }

    @Override
    public void select(AbstractMutableTreeNode abstractMutableTreeNode) {
        tree.setSelectionPath(getTreePath((MockMutableTreeNode) abstractMutableTreeNode));
    }

    @Override
    public void reload(AbstractMutableTreeNode abstractMutableTreeNode) {
        loop(abstractMutableTreeNode);
    }

    @Override
    public void reloadRoot() {
        loop(selected);
    }

    private static void loop(AbstractMutableTreeNode _root) {
        AbstractMutableTreeNode cur_ = _root;
        while (cur_ != null) {
            ((MockMutableTreeNode)cur_).setAccessible(true);
            AbstractMutableTreeNode ch_ = cur_.getChildAt(0);
            if (ch_ != null) {
                cur_ = ch_;
                continue;
            }
            cur_ = next(cur_,_root);
        }
    }
    private static AbstractMutableTreeNode next(AbstractMutableTreeNode _current, AbstractMutableTreeNode _root) {
        AbstractMutableTreeNode n_ = _current;
        while (n_ != null) {
            AbstractMutableTreeNode next_ = n_.getNextSibling();
            if (next_ != null) {
                return next_;
            }
            AbstractMutableTreeNode parent_ = n_.getParent();
            if (parent_ == _root || parent_ == null) {
                n_ = null;
            } else {
                n_ = parent_;
            }
        }
        return null;
    }

    private MockTreePath getTreePath(MockMutableTreeNode _node) {
        MockTreePath tp_ = new MockTreePath();
        MockMutableTreeNode cur_ = _node;
        while (cur_ != null) {
            tp_.getPath().add(0,cur_);
            cur_ = (MockMutableTreeNode) cur_.getParent();
        }
        return tp_;
    }
    @Override
    public AbstractMutableTreeNode getSelected() {
        return selected;
    }

    @Override
    public AbstractMutableTreeNode selectEvt() {
        MockTreePath path_ = tree.getSelectionPath();
        CustList<MockMutableTreeNode> p_ = path_.getPath();
        if (!p_.isEmpty()) {
            selected = p_.last();
        } else {
            selected = null;
        }
        return selected;
    }

    @Override
    public boolean isRootVisible() {
        return tree.isRootVisible();
    }

    @Override
    public void setRootVisible(boolean b) {
        tree.setRootVisible(b);
    }

    @Override
    public AbsCustComponent getTree() {
        return tree;
    }

    @Override
    public void addTreeSelectionListener(AbsShortListTree absShortListTree) {
        list.add(absShortListTree);
        tree.addTreeSelectionListener(absShortListTree);
    }

    @Override
    public int removeTreeSelectionListener(AbsShortListTree absShortListTree) {
        int index_ = list.indexOfObj(absShortListTree);
        list.removeObj(absShortListTree);
        tree.removeTreeSelectionListener(absShortListTree);
        return index_;
    }

    @Override
    public CustList<AbsShortListTree> getTreeSelectionListeners() {
        return list;
    }

    @Override
    public void removeFromParent() {
        selected.removeFromParent();
    }

    @Override
    public void removeAllChildren() {
        selected.removeAllChildren();
    }

    @Override
    public void add(String s) {
        selected.add(new MockMutableTreeNode(s));
    }
}
