using System;
using System.Runtime.InteropServices;

namespace FMS_Adapter
{
    /// <summary>
    /// This class defines the interfacing to the dll file
    /// </summary>
    public class cppToCsharpAdapter
    {
        const string dllPath = "FMS_DLL.dll";



        // init disk
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr makeDiskObject();

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void deleteDiskObject(ref IntPtr THIS);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getLastDiskErrorMessage(IntPtr THIS);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getLastFcbErrorMessage(IntPtr THIS);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void deleteFcbObject(ref IntPtr THIS);

        // Level 0

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void createdisk(IntPtr THIS, string diskName, string diskOwner);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void mountdisk(IntPtr THIS, string diskName);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void unmountdisk(IntPtr THIS);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void recreatedisk(IntPtr THIS, string diskOwner);



        // Level 1
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void format(IntPtr THIS, string diskOwner);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int howmuchempty(IntPtr THIS);


        //Level 2
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void createfile(IntPtr THIS, string fileName, string fileOwner, string FinalOrVar,
                                uint recSize, uint fileSize,
                                string keyType, uint keyOffset, uint keySize = 4, uint algoType=0);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void delfile(IntPtr THIS, string fileName, string fileOwner);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void extendfile(IntPtr THIS, string fileName, string fileOwner, uint size, uint algoType);


        // Level 3
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr openfile(IntPtr THIS, string fileName, string fileOwner, string openMode);


        // FCB
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void closefile(IntPtr THIS);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void readRec(IntPtr THIS, IntPtr dest, bool readForUpdate = false);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void writeRec(IntPtr THIS, IntPtr source);


        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void seekRec(IntPtr THIS, uint from, int pos);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void updateRecCancel(IntPtr THIS);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void deleteRec(IntPtr THIS);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void updateRec(IntPtr THIS, IntPtr source);

        //extra
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void getVolumeHeader(IntPtr THIS, IntPtr buffer);
        
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetEntry(IntPtr THIS, IntPtr buffer, bool p, int i);
    }
}
