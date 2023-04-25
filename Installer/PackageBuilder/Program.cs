using InstallBuilderLib;
using PowerArgs;

public class CLIArgs
{
    [ArgRequired]
    public string PackageDescriptor { get; set; }
    [ArgRequired]
    public string OutputPackage { get; set; }
}
public class Program
{
    static void Main(string[] args)
    {
        string pd = string.Empty, opack = string.Empty;

        try
        {
            var parsed = Args.Parse<CLIArgs>(args);
            pd = parsed.PackageDescriptor;
            opack = parsed.OutputPackage;
        }
         catch(Exception e)
        {
            Console.WriteLine(ArgUsage.GenerateUsageFromTemplate<CLIArgs>());
            Environment.Exit(0);
        }
        Builder builder = new Builder(pd, opack);
        builder.BuildPackage();
    }
}
