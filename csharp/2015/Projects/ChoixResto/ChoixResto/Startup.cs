using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(ChoixResto.Startup))]
namespace ChoixResto
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
