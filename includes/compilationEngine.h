

class CompilationEngine {
  private:
  public:
    CompilationEngine();

    void nextToken();

    bool compile();
    void compileClass();
    void compileClassVarDec();
    void compileSubroutine();
    void compileParameterList();
    void compileSubroutineBody();
    void compileVarDec();
    void compileStatements();
    void compileDo();
    void compileLet();
    void compileWhile();
    void compileReturn();
    void compileIf();
    void compileExpression();
    void compileTerm();
    void compileExpressionList();
    void compileSubroutineCall();
    void compileSubroutineCall(string subName);
}