package code.mock;

import code.expressionlanguage.structs.Struct;
import code.util.IdMap;

public class MockConcurrentMapStructStruct extends MockConcurrentMap<Struct, Struct> {
    public MockConcurrentMapStructStruct() {
        super(new IdMap<Struct, Struct>());
    }
}
