using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class MemoryCompiler
    {
        private Map<String, String> files;
        private StringList refAssemblies;
        private CompilerErrorCollection errors;
        public MemoryCompiler(Map<String, String> _files, StringList _refAssemblies)
        {
            files = _files;
            refAssemblies = _refAssemblies;
        }
        public void compileFiles()
        {
            if (files.isEmpty())
            {
                Constants.reinitAssembly();
                return;
            }
            CompilerParameters parameters_ = new CompilerParameters();
            parameters_.GenerateExecutable = false;
            parameters_.GenerateInMemory = true;
            parameters_.ReferencedAssemblies.AddRange(refAssemblies.ToArray());

            CompilerResults r_ = CodeDomProvider.CreateProvider("CSharp").CompileAssemblyFromSource(parameters_, files.values().ToArray());
            if (r_.Errors.Count > 0)
            {
                Constants.reinitAssembly();
                errors = r_.Errors;
                return;
            }
            Assembly as_ = r_.CompiledAssembly;
            Constants.setAssembly(as_);
        }
        public CompilerErrorCollection getErrors()
        {
            return errors;
        }
    }
}
