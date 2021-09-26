package code.music.impl;

import code.music.core.*;
import jm.music.data.Part;

public final class EvolvedPart implements AbstractPart {
    private final Part part;
    public EvolvedPart(MetaPart _part) {
        part = new Part(_part.getName(), Math.max(0,_part.getInstrument()), _part.getChannel());
        part.setDenominator(_part.getDenominator());
        part.setNumerator(_part.getNumerator());
    }
    public void add(AbstractPhrase _e) {
        part.add(((EvolvedPhrase)_e).getPhrase());
    }

    public Part getPart() {
        return part;
    }
}
