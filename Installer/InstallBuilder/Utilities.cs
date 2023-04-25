using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;

namespace InstallBuilderLib
{
    public class Utilities
    {
        public static string GenerateFileMD5(string filename)
        {
            if (!System.IO.File.Exists(filename))
            {
                throw new FileNotFoundException(string.Format("{0} does not exist", filename));
            }

            using (var md5=MD5.Create())
            {
                using (var stream=File.OpenRead(filename))
                {
                    var hash = md5.ComputeHash(stream);
                    return BitConverter.ToString(hash).Replace("-", "").ToLowerInvariant();
                }
            }
        }
    }
}
