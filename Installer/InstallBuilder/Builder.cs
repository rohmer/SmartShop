using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ICSharpCode.SharpZipLib;
using ICSharpCode.SharpZipLib.BZip2;
using ICSharpCode.SharpZipLib.Zip;

namespace InstallBuilderLib
{
    public class Builder
    {
        string packageFile, packageDesc;
        public Builder(string PackageDescriptor, string OutputPackage)
        {
            packageFile = OutputPackage;
            if(Path.GetExtension(packageFile)!="pkg")
            {
                packageFile += ".pkg";
            }
            packageDesc = PackageDescriptor;
        }

        public bool BuildPackage()
        {
            PackageDescriptor pd;
            try
            {
                PackageDescriptor ptemp = PackageDescriptor.FromFile(packageDesc);
                if (ptemp == null)
                    return false;
                pd = ptemp;
            } catch (Exception)
            {
                return false;
            }
            string workingDir = Path.GetTempPath();
            foreach (FileDescriptor f in pd.PackageFiles)
            {
                Console.WriteLine(string.Format("Generating hash for: {0}", f.SourceFile));
                f.GenerateHash();
                string dest = Path.Combine(workingDir, Path.Combine(f.DestinationFolder, Path.GetFileName(f.SourceFile)));
                try
                {
                    File.Copy(f.SourceFile, dest);
                } catch (Exception e)
                {
                    Console.WriteLine(
                        string.Format("Failed to copy {0} to {1}, ex: {3}",
                            f.SourceFile, dest, e.Message));
                    Directory.Delete(workingDir, true);
                    Environment.Exit(-1);
                }

                string vFile = f.SourceFile += ".json";
                if (File.Exists(vFile))
                {
                    try
                    {
                        f.FileVersion = Version.FromFile(vFile);
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(string.Format("Error getting Version info from ", e.Message));
                        Directory.Delete(workingDir, true);
                        Environment.Exit(-1);
                    }
                }

            }
            string pdFileName= Path.Combine(workingDir, "package.json");
            if (!pd.ToFile(pdFileName))
            {
                Console.WriteLine(string.Format("Error writing package descriptor: {0}, ex: {1}"));
                Directory.Delete(workingDir, true);
                Environment.Exit(-1);
            }

            compressDirectory(workingDir, packageFile, 9);
            return true;
        }


        private void compressDirectory(string DirectoryPath, string OutputFilePath, int CompressionLevel = 9)
        {
            try
            {
                // Depending on the directory this could be very large and would require more attention
                // in a commercial package.
                string[] filenames = Directory.GetFiles(DirectoryPath);

                // 'using' statements guarantee the stream is closed properly which is a big source
                // of problems otherwise.  Its exception safe as well which is great.
                using (ZipOutputStream OutputStream = new ZipOutputStream(File.Create(OutputFilePath)))
                {

                    // Define the compression level
                    // 0 - store only to 9 - means best compression

                    byte[] buffer = new byte[4096];

                    foreach (string file in filenames)
                    {

                        // Using GetFileName makes the result compatible with XP
                        // as the resulting path is not absolute.
                        ZipEntry entry = new ZipEntry(Path.GetFileName(file));

                        // Setup the entry data as required.

                        // Crc and size are handled by the library for seakable streams
                        // so no need to do them here.

                        // Could also use the last write time or similar for the file.
                        entry.DateTime = DateTime.Now;
                        OutputStream.PutNextEntry(entry);

                        using (FileStream fs = File.OpenRead(file))
                        {

                            // Using a fixed size buffer here makes no noticeable difference for output
                            // but keeps a lid on memory usage.
                            int sourceBytes;

                            do
                            {
                                sourceBytes = fs.Read(buffer, 0, buffer.Length);
                                OutputStream.Write(buffer, 0, sourceBytes);
                            } while (sourceBytes > 0);
                        }
                    }

                    // Finish/Close arent needed strictly as the using statement does this automatically

                    // Finish is important to ensure trailing information for a Zip file is appended.  Without this
                    // the created file would be invalid.
                    OutputStream.Finish();

                    // Close is important to wrap things up and unlock the file.
                    OutputStream.Close();

                    Console.WriteLine("Files successfully compressed");
                }
            }
            catch (Exception ex)
            {
                // No need to rethrow the exception as for our purposes its handled.
                Console.WriteLine("Exception during processing {0}", ex);
                Environment.Exit(-1);
            }
        }
    }
}
