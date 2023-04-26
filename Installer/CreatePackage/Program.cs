using InstallBuilderLib;
using PowerArgs;

public class CLIArgs
{
    [ArgRequired]
    public string Package { get; set; }
    [ArgRequired]
    public string Name { get; set; }   
    public string Description { get; set; }
    public string Version { get; set; }
}
public class Program
{
    static void Main(string[] args)
    {
        string name, desc, package;
        InstallBuilderLib.Version version;
        CLIArgs parsed=null;
        try
        {
            parsed = Args.Parse<CLIArgs>(args);
        } catch(Exception e)
        {
            Console.WriteLine(e.Message);
            Console.WriteLine(ArgUsage.GenerateUsageFromTemplate<CLIArgs>());
            Environment.Exit(0);
        }

        name = parsed.Name;
        desc = parsed.Description;
        package = parsed.Package;
        
        if(Path.GetExtension(package)!=".pdef")
        {
            package += ".pdef";
            Console.WriteLine("Setting package name to: " + package);
        }
        string tmpV = parsed.Version;
        if(!string.IsNullOrEmpty(tmpV))
        {
            string[] parts = tmpV.Split('.');
            uint major=0, minor=0, build=0;
            if (parts.Length > 0)
                major = uint.Parse(parts[0]);
            if (parts.Length > 1)
                minor = uint.Parse(parts[1]);
            if (parts.Length > 2)
                build = uint.Parse(parts[2]);
            version = new InstallBuilderLib.Version(major, minor, build);
        } else
        {
            version = new InstallBuilderLib.Version(0, 0, 0);
        }

        PackageDescriptor pd = new PackageDescriptor(name, desc, version);
        try
        {
            pd.ToFile(package);
        } catch(Exception e)
        {
            Console.WriteLine(string.Format("Error writing package: {0}, error: {1}", package, e.Message));
        }

    }
}