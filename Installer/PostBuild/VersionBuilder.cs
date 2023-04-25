using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using InstallBuilderLib;
using Newtonsoft.Json;

namespace PostBuild
{
    public class VersionBuilder
    {
        string src, dest, buildArti;
        public VersionBuilder(string Source, string Dest, string BuildArtifact)
        {
            src = Source;
            dest = Dest;
            buildArti = BuildArtifact;
        }

        public void Process()
        {
            InstallBuilderLib.Version version;
            string versionSrcFile = Path.Combine(src, "version.json");
            try
            {
                version = InstallBuilderLib.Version.FromFile(versionSrcFile);
                if (version == null)
                    version = new InstallBuilderLib.Version();
            } catch (Exception)
            {
                version = new InstallBuilderLib.Version();
            }
            version.BuildNumber++;
            if(!version.ToFile(versionSrcFile))
            {
                Console.WriteLine(string.Format("Could not write {0}", versionSrcFile));
                Environment.Exit(-1);
            }

            string outputFile = Path.Combine(dest, string.Format("{0}.json", buildArti));
            if(!version.ToFile(outputFile))
            {
                Console.WriteLine(string.Format("Could not write {0}", versionSrcFile));
                Environment.Exit(-1);
            }
        }
    }
}
