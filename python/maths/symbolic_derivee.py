import fractions
class MatCommonCst:
    BAD_PRIO = -1
    ADD_PRIO = 1
    MULT_PRIO = 2
    UNARY_PRIO = 3
    FCT_OPER_PRIO = 4
    DOT = '.'[0]
    PAR_LEFT = '('[0]
    PAR_RIGHT = ')'[0]
    SEP_ARG = ','[0]
    MULT_CHAR= '*'[0]
    DIV_CHAR= ':'[0]
    PLUS_CHAR= '+'[0]
    MINUS_CHAR = '-'[0]
    @staticmethod
    def getPrio(_curChar):
        ch = ord(_curChar)
        prioOpMult_ = 0
        if ch == ord(MatCommonCst.MINUS_CHAR) or ch == ord(MatCommonCst.PLUS_CHAR):
            prioOpMult_ = MatCommonCst.ADD_PRIO
        elif ch == ord(MatCommonCst.MULT_CHAR) or ch == ord(MatCommonCst.DIV_CHAR):
            prioOpMult_ = MatCommonCst.MULT_PRIO
        return prioOpMult_

class MathExpUtil:
    CHAR_WORD_OTHER = '_'[0]
    @staticmethod
    def allOp(_curChar) :
        return ord(_curChar) == ord(MatCommonCst.PAR_RIGHT) or MathExpUtil.unary(_curChar) or MathExpUtil.normalOp(_curChar);
    @staticmethod
    def unary(_curChar) :
        return ord(_curChar) == ord(MatCommonCst.PLUS_CHAR) or ord(_curChar) == ord(MatCommonCst.MINUS_CHAR);
    @staticmethod
    def normalOp(_curChar) :
        return MathExpUtil.mult(_curChar) or MathExpUtil.call(_curChar);
    @staticmethod
    def call(_curChar) :
        return ord(_curChar) == ord(MatCommonCst.PAR_LEFT) or ord(_curChar) == ord(MatCommonCst.SEP_ARG);
    @staticmethod
    def mult(_curChar) :
        return ord(_curChar) == ord(MatCommonCst.MULT_CHAR) or ord(_curChar) == ord(MatCommonCst.DIV_CHAR);
    @staticmethod
    def charIs(_string, _len, _i, _ch) :
        return _i < _len and _string[_i] == _ch
    @staticmethod
    def isWordChar(_char) :
        ch = ord(_char)
        if ch == ord(MathExpUtil.CHAR_WORD_OTHER) :
            return True
        if ch < ord('0'[0]) :
            return False
        if ch <= ord('9'[0]) :
            return True
        if ch < ord('A'[0]) :
            return False
        if ch <= ord('Z'[0]) :
            return True
        if ch < ord('a'[0]) :
            return False
        if ch <= ord('z'[0]) :
            return True
        return ch >= 160
    @staticmethod
    def isDigit(_char) :
        ch = ord(_char)
        return ch >= ord('0'[0]) and ch <= ord('9'[0])
    @staticmethod
    def isWhitespace(_char) :
        ch = ord(_char)
        return ch <= ord(' '[0])

class MathState :
    def __init__(self):
        self.index=0
        self.stack={}

class MatVariableInfo :
    def __init__(self):
        self.name=""
        self.firstChar=0
        self.lastChar=0

class MaDelimiters :
    def __init__(self):
        self.operatorsIndexes=[]
        self.numbers=[]
        self.nbParts=[]
        self.varParts=[]
        self.varNames=""
        self.varFcts={}

class MaError :
    def __init__(self):
        self.offset=-1

    def setOffset(self, _index) :
        self.offset = max(0,_index)

    def display(self) :
        return "#"+ str(self.offset)
class MatNumberResult :
    DOT = '.'[0];
    SEP_RATE = '/'[0];

    def __init__(self, _nbInfo, _index) :
        self.nbInfo = _nbInfo;
        self.index = _index;

    @staticmethod
    def build(_from, _string) :
        nbInfo_ = "";
        len_ = len(_string);
        i_ = _from;
        stop_ = False;
        while (i_ < len_) :
            cur_ = _string[i_];
            if (not MathExpUtil.isDigit(cur_)) :
                if (cur_ == MatNumberResult.DOT or cur_ == MatNumberResult.SEP_RATE) :
                    nbInfo_+=str(cur_);
                    i_+=1;
                else :
                    stop_ = True;
                break;
            nbInfo_+=str(cur_);
            i_+=1;
        if i_ >= len_ or stop_ :
            return MatNumberResult(nbInfo_,i_);

        while (i_ < len_) :
            cur_ = _string[i_];
            if (not MathExpUtil.isDigit(cur_)) :
                break;
            nbInfo_+=str(cur_);
            i_+=1;
        
        return MatNumberResult(nbInfo_,i_);


class MatVariableResult :
    def __init__(self,_name,_index):
        self.name = _name
        self.index = _index
    @staticmethod
    def build(_string, _len, _from) :
        name_ = ""
        i_ = _from;
        while i_ < _len :
            last_ = _string[i_]
            if not MathExpUtil.isWordChar(last_) :
                break
            name_+=last_
            i_+=1
        return MatVariableResult(name_,i_)

class MatConstType :
    NUMBER=0
    STRING=1
    LOC_VAR=2
    NOTHING=3
    ERROR=4


class MaOperationsSequence :

    def __init__(self):
        self.fct = ""
        self.prio = 0
        self.parts = {}
        self.opers = {}
        self.kind=-1
        self.offset=0
        self.cst=0
        self.varNames=[]
        self.varFcts={}

    def setupValue(self, _string,  _offset) :
        self.parts = {0:_string}
        self.offset = _offset;
    
    def setupValues(self, _string) :
        self.parts = {}
        if (len(self.opers)==0) :
            self.parts = {0:_string}
            self.kind = MatConstType.ERROR;
            return;
        
        self.feedValues(_string);
    

    def feedValues(self, _string) :
        self.firstOperand(_string);
        keys_=list(self.opers.keys())
        keys_.sort()
        values_ = [self.opers[x] for x in keys_]
        endPart_ = keys_[0];
        if (self.prio == MatCommonCst.FCT_OPER_PRIO) :
            afterLastPar_ = keys_[-1]+1;
            if (len(_string[afterLastPar_:].strip()) > 0) :
                self.opers = {afterLastPar_:""};
                self.prio = MatCommonCst.BAD_PRIO;
                return;
            
        
        if (self.prio == MatCommonCst.FCT_OPER_PRIO and len(self.opers) == 2) :
            beginValuePart_ = endPart_ + len(values_[0]);
            endPart_ = keys_[1];
            str_ = _string[beginValuePart_: endPart_];
            if (len(str_) > 0) :
                self.parts[beginValuePart_]= str_;
            
            return;
        
        i_ = 1;
        nbKeys_ = len(self.opers);
        while (i_ < nbKeys_) :
            beginValuePart_ = endPart_ + len(values_[i_ - 1]);
            endPart_ = keys_[i_];
            str_ = _string[beginValuePart_: endPart_];
            self.parts[beginValuePart_]= str_;
            i_+=1;
        
        if (self.prio != MatCommonCst.FCT_OPER_PRIO) :
            beginValuePart_ = endPart_ + len(values_[-1]);
            str_ = _string[beginValuePart_:];
            self.parts[beginValuePart_]= str_;
        
    

    def firstOperand(self, _string) :
        if (self.prio != MatCommonCst.UNARY_PRIO) :
            beginValuePart_ = 0;
            endValuePart_ = min(list(self.opers.keys())) 
            str_ = _string[beginValuePart_:endValuePart_];
            self.parts[beginValuePart_]=(str_);
        
    

class MathAdvAfUnaryParts :

    def __init__(self, _string, _index, _lastPrintChar) :
        self.opers={}
        self.dels={}
        self.prio=MatCommonCst.FCT_OPER_PRIO;
        self.current = _index;
        self.lastPrintChar = _lastPrintChar;
        self.fct=""
        opUn_ = str(_string[_index]);
        if (MathExpUtil.unary(_string[_index])) :
            self.prio = MatCommonCst.UNARY_PRIO;
            self.opers={_index:opUn_};
            self.current = MathAdvAfUnaryParts.incrementUnary(_string, _index + 1, _lastPrintChar);
        


    def loop(self, _offset, _string, _d) :
        curChar_ = _string[self.current];
        if ((self.current +_offset) not in _d.operatorsIndexes) :
            self.current+=1;
            return;
        

        if (curChar_ == MatCommonCst.PAR_LEFT) :
            if (self.delFct()) :
                self.fct = _string[0:self.current];
                self.opers={self.current:str(MatCommonCst.PAR_LEFT)};

            
            self.dels[self.current]=(curChar_);
    
        
        if (self.comma(curChar_)) :
            self.opers[self.current]= str(curChar_);
        
        if (curChar_ == MatCommonCst.PAR_RIGHT) :
            self.procRight(curChar_);
            return;
        if (len(self.dels) > 0):
            self.current+=1
            return
        
        
        self.procNumOps(_string, curChar_);
    
    

    def comma(self, _curChar) :
        return _curChar == MatCommonCst.SEP_ARG and len(self.dels) == 1 and self.prio == MatCommonCst.FCT_OPER_PRIO;


    def procRight(self, _rightPart) :
        self.dels.pop(max(list(self.dels.keys())));
        if (self.delFct()) :
            self.opers[self.current]= str(_rightPart);
        
        self.current+=1;


    def delFct(self) :
        return len(self.dels) == 0 and self.prio == MatCommonCst.FCT_OPER_PRIO;
    

    def procNumOps(self, _string, _curChar) :
        built_ = "";
        clear_ = False;
        found_ = False;
        increment_ = 1;
        self.procOp(_string, _curChar, built_, clear_, found_, increment_);
    

    def procOp(self, _string,  _curChar, _built, _clearOperators, _foundOperator, _increment) :
        clear_ = _clearOperators;
        found_ = _foundOperator;
        prioSymbol_ = MathAdvAfUnaryParts.getPrio(_curChar);
        if (prioSymbol_ > 0) :
            _built+=str(_curChar);
            self.reducePrio(prioSymbol_);
            if (self.prio == prioSymbol_) :
                clear_ = True;
                found_ = True;
            
        
        self.tryAddOp(_built, clear_, found_, _increment);
    

    def reducePrio(self, _prioSymbol) :
        if (self.prio > _prioSymbol) :
            self.prio = _prioSymbol;
        
    

    def tryAddOp(self, _built,  _clear,  _found,  _increment) :
        if (_found) :
            if (_clear) :
                self.fct = "";
                self.opers.clear();
            
            self.opers[self.current]=( _built);
        
        self.current += _increment;
    

    @staticmethod
    def getPrio(_curChar) :
        return MatCommonCst.getPrio(_curChar);
    
    @staticmethod
    def incrementUnary(_string, _from, _to) :
        j_ = _from;
        while (j_ <= _to) :
            ch_ = _string[j_]
            if (not MathExpUtil.unary(ch_) and not MathExpUtil.isWhitespace(ch_)) :
                break;
            j_+=1;
        
        return j_;

class MaOperationNode :
    PAR_LEFT = '(';
    PAR_RIGHT = ')';

    UNARY_MINUS = "-";

    MULT = "*";

    PLUS = "+";

    MINUS = "-";

    def __init__(self, _indexInEl,  _op):
        self.par = None
        self.nextSib = None
        self.operats = _op
        self.indexExp = _indexInEl
        self.childIndex = 0
        self.res = None

    
    def exportValue(self):
        root_ = self;
        current_ = self;
        str_ = "";
        
        while (current_ is not None) :
            if isinstance(current_, IdMaOperation):
                str_ += "("
            if isinstance(current_, FctMaOperation):
                str_ += current_.fctname+"("
            if isinstance(current_, UnaryMaOperation):
                str_ += current_.oper
            op_ = None;
            if isinstance(current_, MethodMaOperation):
                op_ = current_.first;
            if op_ is not None:
                current_ = op_;
                continue
            if isinstance(current_, ConstantMaOperation):
                str_ += current_.nb
            if isinstance(current_, VariableMaOperation):
                str_ += current_.nb
            while (current_ is not None):
                next_ = current_.nextSib
                if (next_ is not None) :
                    if isinstance(current_.par,NumericMaOperation):
                        str_ += current_.par.oper
                    if isinstance(current_.par,IdMaOperation):
                        str_ += ","
                    current_ = next_
                    break
                parCur_ = current_.par
                if isinstance(parCur_, IdMaOperation):
                    str_ += ")"
                if isinstance(parCur_, FctMaOperation):
                    str_ += ")"
                if parCur_ is None or parCur_ is root_:
                    current_ = None
                    continue
                current_ = parCur_
                
        
        return str_;
    
    @staticmethod
    def wrapped(cur,destpar):
        if isinstance(cur,VariableMaOperation):
            return cur
        if isinstance(cur,ConstantMaOperation):
            return cur
        if isinstance(cur,IdMaOperation):
            return cur
        if isinstance(cur,UnaryMaOperation):
            return cur
        if isinstance(cur,FctMaOperation):
            return cur
        if isinstance(destpar,IdMaOperation):
            return cur
        if isinstance(destpar,UnaryMaOperation):
            operLoc = MaOperationsSequence()
            res=IdMaOperation(cur.indexExp,operLoc)
            res.append(cur)
            return res
        if isinstance(destpar,NumericMaOperation):
            if cur.oper == "+" and destpar.oper != "+":
                operLoc = MaOperationsSequence()
                res=IdMaOperation(cur.indexExp,operLoc)
                res.append(cur)
                return res
            if cur.oper == "-" or cur.oper == ":":
                operLoc = MaOperationsSequence()
                res=IdMaOperation(cur.indexExp,operLoc)
                res.append(cur)
                return res
            if destpar.oper == ":":
                operLoc = MaOperationsSequence()
                res=IdMaOperation(cur.indexExp,operLoc)
                res.append(cur)
                return res
        return cur

    def getExecutableNodesRepl(self,repl) :
        current_ = self;
        if isinstance(current_, VariableMaOperation):
            varName_ = current_.nb
            if varName_ in repl:
                return repl[varName_].getExecutableNodes()
        exp_ = MaOperationNode.createExecOperationNode(current_);
        expRoot_ = exp_;
        while (current_ is not None) :
            op_ = None;
            if isinstance(current_, MethodMaOperation):
                op_ = current_.first;
            if (MaOperationNode.hasToCreateExec(exp_, op_)) :
                if isinstance(op_, VariableMaOperation):
                    varName_ = op_.nb
                    if varName_ in repl:
                        exp_.append(MaOperationNode.wrapped(repl[varName_].getExecutableNodes(),exp_))
                        loc_ = MaOperationNode.createExecOperationNode(op_);
                        loc_.par = exp_
                        exp_ = loc_;
                        current_ = op_;
                        continue;
                loc_ = MaOperationNode.createExecOperationNode(op_);
                exp_.append(loc_);
                exp_ = loc_;
                current_ = op_;
                continue;
            
            while (current_ is not None) :
                op_ = current_.nextSib;
                par_ = exp_.par;
                if (MaOperationNode.hasToCreateExec(par_, op_)) :
                    if isinstance(op_, VariableMaOperation):
                        varName_ = op_.nb
                        if varName_ in repl:
                            par_.append(MaOperationNode.wrapped(repl[varName_].getExecutableNodes(),par_))
                            loc_ = MaOperationNode.createExecOperationNode(op_);
                            loc_.par = exp_
                            exp_ = loc_;
                            current_ = op_;
                            continue;
                    loc_ = MaOperationNode.createExecOperationNode(op_);
                    par_.append(loc_);
                    exp_ = loc_;
                    current_ = op_;
                    break;
                
                if (par_ is None) :
                    current_ = None;
                    continue;
                
                op_ = current_.par;
                if (op_ is self) :
                    current_ = None;
                    continue;
                
                current_ = op_;
                exp_ = par_;
            
        
        return expRoot_;

    def getExecutableNodes(self) :
        current_ = self;
        exp_ = MaOperationNode.createExecOperationNode(current_);
        expRoot_ = exp_;
        while (current_ is not None) :
            op_ = None;
            if isinstance(current_, MethodMaOperation):
                op_ = current_.first;
            if (MaOperationNode.hasToCreateExec(exp_, op_)) :
                loc_ = MaOperationNode.createExecOperationNode(op_);
                exp_.append(loc_);
                exp_ = loc_;
                current_ = op_;
                continue;
            
            while (current_ is not None) :
                op_ = current_.nextSib;
                par_ = exp_.par;
                if (MaOperationNode.hasToCreateExec(par_, op_)) :
                    loc_ = MaOperationNode.createExecOperationNode(op_);
                    par_.append(loc_);
                    exp_ = loc_;
                    current_ = op_;
                    break;
                
                if (par_ is None) :
                    current_ = None;
                    continue;
                
                op_ = current_.par;
                if (op_ is self) :
                    current_ = None;
                    continue;
                
                current_ = op_;
                exp_ = par_;
            
        
        return expRoot_;
    

    @staticmethod
    def hasToCreateExec( _exp,  _op) :
        return isinstance(_exp, MethodMaOperation) and _op is not None;
    

    @staticmethod
    def createExecOperationNode(_root):
        if isinstance(_root, ConstantMaOperation):
            return ConstantMaOperation(_root.indexExp,_root.operats)
        if isinstance(_root, VariableMaOperation):
            return VariableMaOperation(_root.indexExp,_root.operats)
        if isinstance(_root, IdMaOperation):
            return IdMaOperation(_root.indexExp,_root.operats)
        if isinstance(_root, UnaryMaOperation):
            return UnaryMaOperation(_root.indexExp,_root.operats)
        if isinstance(_root, NumericMaOperation):
            return NumericMaOperation(_root.indexExp,_root.operats)
        if isinstance(_root, FctMaOperation):
            return FctMaOperation(_root.indexExp,_root.operats)
        return None

    @staticmethod
    def createOperationNodeAndChild( _index, _op) :
        created_ = MaOperationNode.createOperationNode(_index, _op);
        if (isinstance(created_,MethodMaOperation)) :
            created_.calculateChs();
        
        return created_;
    
    @staticmethod
    def createOperationNode( _index, _op) :
        if (len(_op.opers) == 0) :
            return MaOperationNode.processLeaf(_index,  _op);
        
        if (_op.prio == MatCommonCst.FCT_OPER_PRIO) :
            return MaOperationNode.procFct(_index,  _op);
        
        return MaOperationNode.procSymbol(_index,  _op);
    

    @staticmethod
    def procSymbol( _index,    _op) :
        if (_op.prio == MatCommonCst.UNARY_PRIO) :
            return MaOperationNode.procUnary(_index, _op);
        
        if (_op.prio == MatCommonCst.MULT_PRIO) :
            return NumericMaOperation(_index, _op);
        
        if (_op.prio == MatCommonCst.ADD_PRIO) :
            return NumericMaOperation(_index, _op);
        
        return None;
    

    @staticmethod
    def processLeaf( _index,  _op) :
        if (_op.kind == MatConstType.LOC_VAR) :
            return VariableMaOperation(_index, _op);
        
        if (_op.kind == MatConstType.NUMBER) :
            return ConstantMaOperation(_index,  _op);
        
        return None;
    

    @staticmethod
    def procUnary( _index,   _op) :
        return UnaryMaOperation(_index,  _op);
    

    @staticmethod
    def procFct( _index,    _op) :
        if len(_op.fct.strip()) > 0:
            return FctMaOperation(_index,  _op);
        return IdMaOperation(_index,  _op);

    def calculate(self, _error, _del):
        pass

class MethodMaOperation(MaOperationNode):

    def __init__(self, _indexInEl,   _op):
        super().__init__(_indexInEl,  _op)
        self.first = None
        self.chs={}

    def getChildren(self) :
        list_ = [];
        elt_ = self.first;
        while (elt_ is not None) :
            list_.append(elt_);
            elt_ = elt_.nextSib;
        
        return list_;
    

    def calculateChs(self):
        pass

    def append(self, _child) :
        _child.par = self
        if (self.first is None) :
            self.first = _child;
            return;
        self.tryAppend(_child);
    

    def tryAppend(self, _child) :
        child_ = self.first;
        while (True) :
            sibling_ = child_.nextSib;
            if (sibling_ is None) :
                child_.nextSib=(_child);
                _child.childIndex=child_.childIndex+1
                return;
            
            child_ = sibling_;
        
    
class ConstantMaOperation(MaOperationNode) :
    def __init__(self, _indexInEl,  _op):
        super().__init__(_indexInEl, _op)
        keys_ = list(_op.parts.keys())
        self.nb=_op.parts[keys_[0]]

    def calculate(self, _error, _del) :
        begin_ = self.operats.cst;
        nb_ = _del.nbParts[begin_];
        try:
            fractions.Fraction(nb_)
            operLoc =  MaOperationsSequence()
            operLoc.setupValue("0", 0);
            self.res=ConstantMaOperation(self.indexExp,operLoc)
            return;
        except:
            _error.setOffset(self.indexExp); 
            
            
    
class VariableMaOperation(MaOperationNode) :
    def __init__(self, _indexInEl,  _op):
        super().__init__(_indexInEl, _op)
        keys_ = list(_op.parts.keys())
        self.nb=_op.parts[keys_[0]].strip()

    def calculate(self, _error, _del) :
       operLoc =  MaOperationsSequence()
       if self.nb == self.operats.varNames:
           operLoc.setupValue("1", 0);
       else:
           operLoc.setupValue("0", 0);
       self.res=ConstantMaOperation(self.indexExp,operLoc)

class FctMaOperation(MethodMaOperation):
    def __init__(self, _indexInEl,  _op):
        super().__init__(_indexInEl, _op)
        self.fctname = _op.fct

    def calculate(self, _error, _del) :
        chidren_ = self.getChildren();
        len_ = len(chidren_);
        if (len_ != 1) :
            _error.setOffset(self.indexExp); 
            return;
        if self.fctname not in self.operats.varFcts:
            _error.setOffset(self.indexExp); 
            return
        expDer = self.operats.varFcts[self.fctname]
        calc = MaParser.analyzeCalculateQuick(expDer,_error,self.operats.varNames,self.operats.varFcts);
        repl = {self.operats.varNames:self.first}
        operLoc = MaOperationsSequence()
        operLoc.opers[0]="*"
        contProdOne = NumericMaOperation(self.indexExp,operLoc)
        contProdOne.append(MaOperationNode.wrapped(self.first.res,contProdOne))
        contProdOne.append(MaOperationNode.wrapped(calc.getExecutableNodesRepl(repl),contProdOne))
        self.res=contProdOne

    def calculateChs(self) :
        vs_ = self.operats.parts;
        vs_.pop(min(list(self.operats.parts.keys())));
        for k,v in vs_.items():
            self.chs[k] = v

class IdMaOperation(MethodMaOperation):
    def __init__(self, _indexInEl,  _op):
        super().__init__(_indexInEl, _op)

    def calculate(self, _error, _del) :
        chidren_ = self.getChildren();
        len_ = len(chidren_);
        if (len_ == 2) :
            fch = self.first
            sch = fch.nextSib
            operLoc = MaOperationsSequence()
            compo = IdMaOperation(self.indexExp,operLoc)
            compo.append(fch.res)
            compo.append(sch.getExecutableNodes())
            operLoc = MaOperationsSequence()
            operLoc.opers[0]="*"
            contProdOne = NumericMaOperation(self.indexExp,operLoc)
            contProdOne.append(MaOperationNode.wrapped(sch.res,contProdOne))
            contProdOne.append(MaOperationNode.wrapped(compo,contProdOne))
            self.res=contProdOne
            return;
        if (len_ != 1) :
            _error.setOffset(self.indexExp); 
            return;
        fch = self.first
        self.res=MaOperationNode.wrapped(fch.res,self)

    def calculateChs(self) :
        vs_ = self.operats.parts;
        vs_.pop(min(list(self.operats.parts.keys())));
        for k,v in vs_.items():
            self.chs[k] = v
    
class UnaryMaOperation(MethodMaOperation):
    def __init__(self, _indexInEl,  _op):
        super().__init__(_indexInEl, _op)
        keys_ = list(_op.opers.keys())
        self.oper =_op.opers[keys_[0]]

    def calculate(self, _error, _del) :
        chidren_ = self.getChildren();
        len_ = len(chidren_);
        if (len_ != 1) :
            _error.setOffset(self.indexExp); 
            return;
        fch = self.first
        self.res=MaOperationNode.wrapped(fch.res,self)

    def calculateChs(self) :
        vs_ = self.operats.parts;
        for k,v in vs_.items():
            self.chs[k] = v

class NumericMaOperation(MethodMaOperation):
    def __init__(self, _indexInEl,  _op):
        super().__init__(_indexInEl, _op)
        keys_ = list(_op.opers.keys())
        self.oper =_op.opers[keys_[0]]

    def calculate(self, _error, _del) :
        oper_ = self.operats.opers[min(list(self.operats.opers.keys()))];
        self.processRates(_error, oper_);

    def processRates(self,_error, _oper) :
        if (_oper == "+" or _oper == "-") :
            fch = self.first
            sch = fch.nextSib
            operLoc = MaOperationsSequence()
            operLoc.opers[0]=self.operats.opers[min(list(self.operats.opers.keys()))]
            cont = NumericMaOperation(self.indexExp,operLoc)
            cont.oper = self.oper
            cont.append(MaOperationNode.wrapped(fch.res,cont))
            cont.append(MaOperationNode.wrapped(sch.res,cont))
            self.res=cont
            return;
        if (_oper == "*") :
            fch = self.first
            sch = fch.nextSib
            operLoc = MaOperationsSequence()
            operLoc.opers[0]="*"
            contProdOne = NumericMaOperation(self.indexExp,operLoc)
            contProdOne.append(MaOperationNode.wrapped(fch.getExecutableNodes(),contProdOne))
            contProdOne.append(MaOperationNode.wrapped(sch.res,contProdOne))
            operLoc = MaOperationsSequence()
            operLoc.opers[0]="*"
            contProdTwo = NumericMaOperation(self.indexExp,operLoc)
            contProdTwo.append(MaOperationNode.wrapped(fch.res,contProdTwo))
            contProdTwo.append(MaOperationNode.wrapped(sch.getExecutableNodes(),contProdTwo))
            operLoc = MaOperationsSequence()
            operLoc.opers[0]="+"
            contSum = NumericMaOperation(self.indexExp,operLoc)
            contSum.append(contProdOne)
            contSum.append(contProdTwo)
            self.res=contSum
            return;
        if (_oper == ":") :
            fch = self.first
            sch = fch.nextSib
            operLoc = MaOperationsSequence()
            operLoc.opers[0]="*"
            contProdOne = NumericMaOperation(self.indexExp,operLoc)
            contProdOne.append(MaOperationNode.wrapped(fch.getExecutableNodes(),contProdOne))
            contProdOne.append(MaOperationNode.wrapped(sch.res,contProdOne))
            operLoc = MaOperationsSequence()
            operLoc.opers[0]="*"
            contProdTwo = NumericMaOperation(self.indexExp,operLoc)
            contProdTwo.append(MaOperationNode.wrapped(fch.res,contProdTwo))
            contProdTwo.append(MaOperationNode.wrapped(sch.getExecutableNodes(),contProdTwo))
            operLoc = MaOperationsSequence()
            operLoc.opers[0]="-"
            contSum = NumericMaOperation(self.indexExp,operLoc)
            contSum.append(contProdTwo)
            contSum.append(contProdOne)
            operLoc = MaOperationsSequence()
            operLoc.opers[0]="*"
            contProd = NumericMaOperation(self.indexExp,operLoc)
            contProd.append(MaOperationNode.wrapped(sch.getExecutableNodes(),contProd))
            contProd.append(MaOperationNode.wrapped(sch.getExecutableNodes(),contProd))
            operLoc = MaOperationsSequence()
            operLoc.opers[0]=":"
            contRatio = NumericMaOperation(self.indexExp,operLoc)
            contRatio.append(MaOperationNode.wrapped(contSum,contRatio))
            contRatio.append(MaOperationNode.wrapped(contProd,contRatio))
            self.res=contRatio
            return;
        _error.setOffset(self.indexExp);    

    def calculateChs(self) :
        vs_ = self.operats.parts;
        for k,v in vs_.items():
            self.chs[k] = v
    


#package code.maths.litteraladv;
#
class MaParser :
#    private MaParser() {
#    }
#
#    public static String processEl(String _el, CustList<Replacement> _conf) {
#        MaParameters aliases_ = new MaParameters();
#        String outVars_ = checkedVariables(_conf);
#        if (!outVars_.isEmpty()) {
#            return outVars_;
#        }
#        StringMap<MaStruct> values_ = new StringMap<MaStruct>();
#        StringList varNames_ = new StringList();
#        StringMap<String> repl_ = new StringMap<String>();
#        for (Replacement r: _conf) {
#            String user_ = r.getOldString();
#            values_.addEntry(user_,null);
#            varNames_.add(user_);
#            repl_.addEntry(user_,r.getNewString());
#        }
#        String strValues_ = feedVars(aliases_, repl_, values_, varNames_);
#        if (!strValues_.isEmpty()) {
#            return strValues_;
#        }
#        MaError err_ = new MaError();
#        MaStruct out_ = analyzeCalculate(_el, values_, aliases_, err_, false, varNames_);
#        return MaNumParsers.toStrNb(out_,err_);
#    }
#
#    private static String feedVars(MaParameters _aliases, StringMap<String> _repl, StringMap<MaStruct> _values, StringList _varNames) {
#        String message_;
#        while (true) {
#            Res res_ = res(_aliases, _repl, _values, _varNames);
#            if (!res_.isCalculated()) {
#                message_ = res_.getMessage();
#                break;
#            }
#        }
#        return message_;
#    }
#    private static Res res(MaParameters _aliases, StringMap<String> _repl, StringMap<MaStruct> _values, StringList _varNames) {
#        boolean calculatedValue_ = false;
#        int index_ = 0;
#        for (EntryCust<String,String> e: _repl.entryList()) {
#            if (_values.getValue(index_) == null) {
#                String cf_ = StringUtil.nullToEmpty(e.getValue());
#                MaError err_ = new MaError();
#                MaStruct val_ = analyzeCalculate(cf_, _values, _aliases, err_, true, _varNames);
#                if (val_ != null) {
#                    _values.setValue(index_, val_);
#                    calculatedValue_ = true;
#                    break;
#                }
#                if (err_.getOffset() > -1) {
#                    return new Res(false, "#" + e.getKey()+"#"+err_.getOffset());
#                }
#            }
#            index_++;
#        }
#        return new Res(calculatedValue_,"");
#    }
#    private static String checkedVariables(CustList<Replacement> _conf) {
#        StringList allVars_ = new StringList();
#        for (Replacement r: _conf) {
#            String user_ = r.getOldString();
#            if (!MathExpUtil.isWord(user_)) {
#                return "###"+user_+"#"+r.getNewString();
#            }
#            if (StringUtil.contains(allVars_,user_)) {
#                return "##"+user_+"#"+r.getNewString();
#            }
#            allVars_.add(user_);
#        }
#        return "";
#    }
#    private static String checkedAliases(String _el, CustList<Replacement> _conf) {
#        for (Replacement r: _conf) {
#            if (koCoreRepl(r)) {
#                return "####" + _el;
#            }
#        }
#        return "";
#    }
#
    @staticmethod
    def analyzeCalculate( _el, _err, _varNames, _varFcts) :
        if len(_varNames) == 0:
            return None
        if MathExpUtil.isDigit(_varNames[0]):
            return None
        d_ = MaParser.checkSyntax(_el, _err,_varNames);
        d_.varFcts = _varFcts
        if (_err.offset > -1) :
            return None;
        
        opTwo_ = MaParser.getOperationsSequence(0, _el, d_);
        op_ = MaOperationNode.createOperationNodeAndChild(0, opTwo_);
        if (op_ == None) :
            _err.setOffset(0);
            return None;
        
        all_ = MaParser.getSortedDescNodes(op_, _err, d_);
        if (_err.offset > -1) :
            return None;
        
        MaParser.calculate(all_,  _err,d_);
        if (_err.offset > -1) :
            return None;
        
        return op_.res;

    @staticmethod
    def analyzeCalculateQuick( _el, _err, _varNames, _varFcts) :
        if len(_varNames) == 0:
            return None
        if MathExpUtil.isDigit(_varNames[0]):
            return None
        d_ = MaParser.checkSyntax(_el, _err,_varNames);
        d_.varFcts = _varFcts
        if (_err.offset > -1) :
            return None;
        
        opTwo_ = MaParser.getOperationsSequence(0, _el, d_);
        op_ = MaOperationNode.createOperationNodeAndChild(0, opTwo_);
        if (op_ == None) :
            _err.setOffset(0);
            return None;
        
        MaParser.getSortedDescNodes(op_, _err, d_);
        if (_err.offset > -1) :
            return None;
        
        return op_;
    

    @staticmethod
    def getSortedDescNodes( _root,  _error,  _del) :
        list_ = [];
        c_ = _root;
        while (c_ is not None) :
            c_ = MaParser.getAnalyzedNext(c_, _root, list_, _error, _del);
        
        return list_;
    

    @staticmethod
    def getAnalyzedNext( _current,  _root,  _sortedNodes,  _error,  _del) :
        next_ = MaParser.createFirstChild(_current, _error, _del);
        if (_error.offset > -1) :
            return None;
        
        if (next_ is not None) :
            _current.append(next_);
            return next_;
        
        current_ = _current;
        while (True) :
            current_.order=len(_sortedNodes);
            _sortedNodes.append(current_);
            next_ = MaParser.createNextSibling(current_, _error, _del);
            if (_error.offset > -1) :
                return None;
            
            if (next_ is not None) :
                next_.par = current_.par
                next_.par.append(next_);
                return next_;
            
            par_ = current_.par;
            if (par_ is _root) :
                par_.order=len(_sortedNodes);
                _sortedNodes.append(par_);
                return None;
            
            if (par_ is None) :
                return None;
            
            current_ = par_;
        
    @staticmethod
    def createFirstChild( _block,  _error,  _delimiter) :
        if (not(isinstance(_block,MethodMaOperation))) :
            return None;
        
        if (len(_block.chs) == 0) :
            return None;
        keys_ = list(_block.chs.keys())
        keys_.sort()
        value_ = _block.chs[keys_[0]];
        curKey_ = keys_[0];
        offset_ = _block.indexExp+curKey_;
        r_ = MaParser.getOperationsSequence(offset_, value_, _delimiter);
        op_ = MaOperationNode.createOperationNodeAndChild(offset_, r_);
        if (op_ is None) :
            _error.setOffset(offset_);
            return None;
        
        return op_;
    

    @staticmethod
    def createNextSibling( _block,  _error,  _delimiter) :
        p_ = _block.par;
        if (p_ is None) :
            return None;
        
        keys_ = list(p_.chs.keys())
        keys_.sort()
        nextIndex_ = _block.childIndex + 1;
        if (nextIndex_ >= len(keys_)) :
            return None;
        
        value_ = p_.chs[keys_[nextIndex_]];
        curKey_ = keys_[nextIndex_];
        offset_ = p_.indexExp+curKey_;
        r_ = MaParser.getOperationsSequence(offset_, value_, _delimiter);
        op_ = MaOperationNode.createOperationNodeAndChild(offset_, r_);
        if (op_ is None) :
            _error.setOffset(offset_);
            return None;
        
        return op_;
    

    @staticmethod
    def calculate( _nodes,  _error,  _del) :
        fr_ = 0;
        len_ = len(_nodes);
        while (fr_ < len_) :
            o = _nodes[fr_];
            o.calculate(_error,_del);
            if (_error.offset > -1) :
                return;
            
            fr_ = fr_+1;
        
    
    @staticmethod
    def checkSyntax(_string, _error, _varNames) :
        d_ = MaDelimiters();
        d_.varNames = _varNames
        len_ = len(_string);
        i_ = 0;
        while i_ < len_ :
            if not MathExpUtil.isWhitespace(_string[i_]) :
                break
            i_+=1
        if i_ >= len_:
            _error.setOffset(i_)
            return d_
        m_ = MathState()
        while m_.index < len_ :
            MaParser.loop(_string, _error, d_, len_, m_,_varNames)
        return MaParser.redirect(_error, m_,d_);

    @staticmethod
    def loop(_string, _error, _d, _len, _m, _varNames) :
        curChar_ = _string[_m.index]
        if MathExpUtil.isWordChar(curChar_) :
            _m.index=(MaParser.processWordChar(_string, _d, _len, _m.index, curChar_))
            return;

        if curChar_ == MatCommonCst.DOT and MaParser.charIsDig(_string,_m) :
            j_ = MaParser.addNumberInfo(_d, _m.index + 1, _m.index, _string)
            _d.nbParts[-1]='.'+_d.nbParts[-1]
            _m.index=(j_)
            return
        s_ = _m.stack
        MaParser.processLeftDel(_m, curChar_, s_, MatCommonCst.PAR_LEFT)
        MaParser.processRightDel(_m, curChar_,_len,_error,MatCommonCst.PAR_LEFT,MatCommonCst.PAR_RIGHT)
        if curChar_ == MatCommonCst.SEP_ARG and len(s_) == 0 :
            _error.setOffset(_m.index)
            _m.index=(_len)
        if _error.offset > -1 :
            return
        _m.index=(MaParser.procOper(_d, _m.index, curChar_))

    @staticmethod
    def processLeftDel(_m, _curChar, _s, _left) :
        if (_curChar == _left) :
            _s[_m.index] = _left;

    @staticmethod
    def processRightDel(_m, _curChar, _len, _error, _leftChar, _rightChar) :
        s_ = _m.stack;
        if (_curChar == _rightChar) :
            if (MaParser.misMatchDel(s_, _leftChar)) :
                _error.setOffset(_m.index);
                _m.index=(_len);
                return;
            s_.pop(max(list(s_.keys())));


    @staticmethod
    def misMatchDel(_s, _left) :
        keys_ = list(_s.keys())
        return len(_s) == 0 or _s[max(keys_)] != _left;

    @staticmethod
    def mcharIsDig(_string, _m) :
        index_ = _m.index + 1
        return index_ < len(_string) and MathExpUtil.isDigit(_string[index_])
    @staticmethod
    def redirect(_error, _state, _d) :
        if (len(_state.stack) > 0 and _error.offset < 0) :
            _error.setOffset(_state.index);
        return _d;

    @staticmethod
    def processWordChar(_string, _d, _len, _from, _curChar) :
        if (MaParser.isDigitFirst(_string, _len, _from, _curChar)) :
            return MaParser.addNumberInfo(_d, _from, _from, _string);
        var_ = MatVariableInfo()
        var_.firstChar=(_from);
        res_ = MatVariableResult.build(_string, _len, _from);
        i_ = res_.index;
        var_.lastChar=(i_);
        var_.name=(res_.name);
        _d.varParts.append(var_);
        return i_;

    @staticmethod
    def isDigitFirst(_string, _len, _from, _curChar) :
        if not MathExpUtil.isDigit(_curChar):
            return False;
        i_ = _from+1;
        while (i_ < _len) :
            ch_ = _string[i_];
            if (not MathExpUtil.isWordChar(ch_)) :
                break;
            i_+=1;
        return True;

    @staticmethod
    def skipWhite(_string, _len, _from) :
        to_ = _from;
        while (to_ < _len) :
            ch_ = _string[to_];
            if not MathExpUtil.isWhitespace(ch_):
                break;
            to_+=1;
        return to_;

    @staticmethod
    def addNumberInfo(_d, _from, _begin, _string) :
        res_ = MaParser.build(_from, _string);
        i_ = res_.index;
        _d.numbers.append(_begin);
        _d.numbers.append(i_);
        _d.nbParts.append(res_.nbInfo);
        return i_;

    @staticmethod
    def build( _from, _string) :
        nbInfo_ = "";
        len_ = len(_string);
        i_ = _from;
        frac_ = False;
        while i_ < len_:
            cur_ = _string[i_];
            if (cur_ == MatNumberResult.SEP_RATE) :
                nbInfo_+=str(cur_);
                i_+=1;
                frac_ = True;
            elif (MaParser.isWhitePart(_string, len_, i_, cur_) or MaParser.followFrac(frac_, cur_)) :
                nbInfo_+=str(cur_);
                i_+=1;
            elif (MaParser.digOrDot(cur_)) :
                nbInfo_+=str(cur_);
                i_+=1;
                frac_ = False;
            else :
                break;
        return MatNumberResult(nbInfo_,i_);

    @staticmethod
    def isWhitePart( _string,  _len,  _i,  _cur) :
        return MathExpUtil.isWhitespace(_cur) and MaParser.nbPart(_string, _len, _i);


    @staticmethod
    def nbPart( _string,  _len,  _current) :
        next_ = MaParser.skipWhite(_string, _len, _current);
        if (next_ >= _len) :
            return False;
        
        ch_ = _string[next_];
        return MaParser.nbPart2(ch_);
    
    @staticmethod
    def nbPart2(_cur) :
        return _cur == MatNumberResult.SEP_RATE or MaParser.digOrDot(_cur);
    

    @staticmethod
    def digOrDot(_cur) :
        return MathExpUtil.isDigit(_cur) or _cur == MatNumberResult.DOT;
    

    @staticmethod
    def followFrac( _frac,  _cur) :
        return _cur == '-' and _frac;
    

    @staticmethod
    def procOper(_d, _i, _curChar) :
        if (MathExpUtil.allOp(_curChar)) :
            _d.operatorsIndexes.append(_i);
        
        return _i+1;
    
    @staticmethod
    def getOperationsSequence( _offset,  _string, _d) :
        len_ = len(_string);
        i_ = 0;
        while (i_ < len_ and MathExpUtil.isWhitespace(_string[i_])) :
            i_+=1;
        
        if (i_ >= len_) :
            op_ = MaOperationsSequence();
            op_.varNames = _d.varNames
            op_.varFcts = _d.varFcts
            op_.opers=({});
            op_.setupValue(_string,0);
            return op_;
        
        lastPrintChar_ = len_ - 1;
        while (MathExpUtil.isWhitespace(_string[lastPrintChar_])) :
            lastPrintChar_-=1;
        
        len_ = lastPrintChar_+1;
        for v in _d.varParts :
            if (v.firstChar == _offset + i_) :
                iVar_ = v.lastChar;
                if (iVar_ != _offset + lastPrintChar_ + 1) :
                    break;
                
                op_ = MaOperationsSequence();
                op_.varNames = _d.varNames
                op_.varFcts = _d.varFcts
                op_.kind=(MatConstType.LOC_VAR);
                op_.opers=({});
                op_.setupValue(v.name,i_);
                return op_;
            
        try:
            begin_ = _d.numbers.index( _offset + i_);
            end_ = _d.numbers.index( _offset + lastPrintChar_ + 1);
            if (MaParser.delimits(begin_, end_)) :
                op_ = MaOperationsSequence();
                op_.varNames = _d.varNames
                op_.varFcts = _d.varFcts
                op_.cst=(begin_//2);
                op_.kind=(MatConstType.NUMBER);
                op_.opers=({});
                op_.setupValue(_string,i_);
                return op_;
        except:
            pass
        mat_ = MathAdvAfUnaryParts(_string,i_, lastPrintChar_);
        while (mat_.current < len_) :
            mat_.loop(_offset, _string, _d);
        
        op_ = MaOperationsSequence();
        op_.varNames = _d.varNames
        op_.varFcts = _d.varFcts
        op_.prio=mat_.prio;
        op_.opers=mat_.opers;
        op_.fct=mat_.fct;
        op_.setupValues(_string);
        return op_;
    

    @staticmethod
    def delimits(_begin,_end) :
        return _begin > -1 and _begin + 1 == _end



# datader = {"ln":"1:x","exp":"exp(x)"}
# err_ = MaError()
# result = MaParser.analyzeCalculate("x*y",err_,"x",datader)
# print(result.exportValue())
# result2=MaParser.analyzeCalculate(result.exportValue(),err_,"y",datader)
# print(result2.exportValue())
# result = MaParser.analyzeCalculate("x*y",err_,"y",datader)
# print(result.exportValue())
# result2=MaParser.analyzeCalculate(result.exportValue(),err_,"x",datader)
# print(result2.exportValue())
# result = MaParser.analyzeCalculate("1:x",err_,"x",datader)
# print(result.exportValue())
# result = MaParser.analyzeCalculate("(x*x,x+1)",err_,"x",datader)
# print(result.exportValue())
# result = MaParser.analyzeCalculate("ln(x)",err_,"x",datader)
# print(result.exportValue())
# result = MaParser.analyzeCalculate("ln(x*x)",err_,"x",datader)
# print(result.exportValue())
# result = MaParser.analyzeCalculate("exp(x*x)",err_,"x",datader)
# print(result.exportValue())
# result = MaParser.analyzeCalculate("1:ln(x)",err_,"x",datader)
# print(result.exportValue())
# result = MaParser.analyzeCalculate("(1:x,ln(x))",err_,"x",datader)
# print(result.exportValue())
# result = MaParser.analyzeCalculate("(ln(x),1:x)",err_,"x",datader)
# print(result.exportValue())