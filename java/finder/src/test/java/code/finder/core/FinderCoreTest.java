package code.finder.core;

import static org.junit.Assert.*;

import org.junit.Test;

public class FinderCoreTest {

    @Test
    public void nbMatches1() {
        assertEquals(0, nbMatches("HELLO","A","A"));
    }

    @Test
    public void nbMatches2() {
        assertEquals(0, nbMatches("HELLO","","A"));
    }

    @Test
    public void nbMatches3() {
        assertEquals(0, nbMatches("HELLO","A",""));
    }

    @Test
    public void nbMatches4() {
        assertEquals(0, nbMatches("HELLO","",""));
    }

    @Test
    public void nbMatches5() {
        assertEquals(2, nbMatches("HELLO","*E*","E"));
    }

    @Test
    public void nbMatches6(){
        assertEquals(0, nbMatches("LO","*E*","E"));
    }

    @Test
    public void nbMatches7() {
        assertEquals(3, nbMatches("HELLO","*L*","L"));
    }

    @Test
    public void nbMatches8() {
        assertEquals(4, nbMatches("HEL\nLO","*\\n*L*","L"));
    }

    @Test
    public void nbMatches9() {
        assertEquals(0, nbMatches("HEL\nLO","*\\n*E*",""));
    }

    @Test
    public void nbMatches10() {
        assertEquals(0, nbMatches("HEL\nLO","*\\nE*","O"));
    }

    @Test
    public void nbMatches11() {
        assertEquals(0, nbMatches("HEL\nLO","*\\nE*","L"));
    }

    @Test
    public void nbMatches12() {
        assertEquals(0, nbMatches("HEL\nLO","*\\nL*","F"));
    }

    @Test
    public void nbMatches13() {
        assertEquals(0, nbMatches("HEL\nLO","","?"));
    }

    @Test
    public void nbMatches14() {
        assertEquals(1, nbMatches("HEL\\nLO","*\\\\*",""));
    }
    private static int nbMatches(String _input, String _content, String _regex) {
        return FinderCore.nbMatches(FinderCore.filterList(_content),_input,FinderCore.patternOrNull(_regex));
    }
}