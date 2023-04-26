using InstallBuilderLib;
using PowerArgs;

public class CLIArgs
{
    [ArgRequired]
    public string PackageFile { get; set; }
    public bool Add { get; set; }
    public bool Clear { get; set; }
    public string File { get; set; }
    public InstallBuilderLib.eFileType FileType { get; set; }
    public string Version { get; set; }
}
public class Program
{
    static void Main(string[] args)
    {
        string pd = string.Empty, file = string.Empty;
        bool add = false, clear = false;
        InstallBuilderLib.eFileType ft = InstallBuilderLib.eFileType.SYSTEM;

        InstallBuilderLib.Version version=null;
        try
        {
            var parsed = Args.Parse<CLIArgs>(args);
            pd = parsed.PackageFile;
            file = parsed.File;
            add = parsed.Add;
            clear = parsed.Clear;
            ft = parsed.FileType;

            string tmpV = parsed.Version;
            Console.WriteLine("Checking for Version file: " + file + ".json");
            if (File.Exists(file + ".json"))
            {
                version = InstallBuilderLib.Version.FromFile(file + ".json");
                Console.WriteLine(string.Format("Using Version file, version {0}", version.ToString()));

            }
            else
            {
                Console.WriteLine("Version file does not exist");
            }

            if (!string.IsNullOrEmpty(tmpV))
            {
                string[] parts = tmpV.Split('.');
                uint major = 0, minor = 0, build = 0;
                if (parts.Length > 0)
                    major = uint.Parse(parts[0]);
                if (parts.Length > 1)
                    minor = uint.Parse(parts[1]);
                if (parts.Length > 2)
                    build = uint.Parse(parts[2]);
                version = new InstallBuilderLib.Version(major, minor, build);
            }
            else
            {
                version = new InstallBuilderLib.Version(0, 0, 0);
            }
        } catch (Exception e)
        {
            Console.WriteLine(e.Message);
            Console.WriteLine(ArgUsage.GenerateUsageFromTemplate<CLIArgs>());
            Environment.Exit(0);
        }
        try
        {
            if (add && clear)
            {
                Console.WriteLine(ArgUsage.GenerateUsageFromTemplate<CLIArgs>());
                Environment.Exit(-1);
            }
            if(add && string.IsNullOrWhiteSpace(file))
            {
                Console.WriteLine("Add option requires a file");
                Console.WriteLine(ArgUsage.GenerateUsageFromTemplate<CLIArgs>());
                Environment.Exit(-1);
            }

            InstallBuilderLib.PackageDescriptor package = InstallBuilderLib.PackageDescriptor.FromFile(pd);
            if(clear)
            {
                package.PackageFiles.Clear();
                if(!package.ToFile(pd))
                {
                    Console.WriteLine("Error writing package");
                    Environment.Exit(-1);
                }
            }
            if(add && File.Exists(file))
            {
                string output =String.Empty;
                switch(ft)
                {
                    case eFileType.DEVICE:
                        output = "Devices\\";
                        break;
                    case eFileType.UI:
                        output = "UI\\";
                        break;
                    default:
                        break;
                }
                FileDescriptor fd = new FileDescriptor(file, output, ft, version);

                bool exists = false;
                string fn = string.Empty;
                InstallBuilderLib.Version fv;
                foreach (FileDescriptor f in package.PackageFiles)
                    if (f.DestinationFolder == output && f.SourceFile == fd.SourceFile)
                    {
                        exists = true;
                        fn = f.SourceFile;
                        f.FileVersion = version; ;
                    }

                if (!exists)
                    package.PackageFiles.Add(fd);
                else
                {
                    Console.WriteLine(string.Format("File: {0} exists in package already, updating version to {1}", fn, version.ToString()));
                }
                package.ToFile(pd);
            }

        }
        catch (Exception e)
        {
            Console.WriteLine(string.Format("Exception building package, {0}", e.Message));
            Environment.Exit(-1);
        }

    }
}