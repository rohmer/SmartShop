using System;
using PowerArgs;

namespace PostBuild
{
    public class CLIArgs
    {
        [ArgRequired]
        public string SourceDirectory { get; set; }
        [ArgRequired]
        public string DestinationDirectory { get; set; }
        [ArgRequired]
        public string BuildArtifact { get; set; }
    }
    public class Program
    {
        static void Main(string[] args)
        {
            string src = string.Empty, dest = string.Empty;
            string buildArti = string.Empty;
            try
            {
                var parsed = Args.Parse<CLIArgs>(args);
                src = parsed.SourceDirectory;
                dest = parsed.DestinationDirectory;
                buildArti = parsed.BuildArtifact;
            }
            catch (ArgException ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ArgUsage.GenerateUsageFromTemplate<CLIArgs>());
                Environment.Exit(-1);
            }

            VersionBuilder vb = new VersionBuilder(src, dest, buildArti);
            vb.Process();

            return;

        }
    }
}