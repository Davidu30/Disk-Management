using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_Adapter
{
    public class Disk
    {
        IntPtr myDiskPointer;
        /// <name>
        /// constractor with out parameters
        /// </name>
        /// <summary>
        /// constractor with out parameters-Update fields of disk
        /// </summary>
        public Disk()
        {
            this.myDiskPointer = cppToCsharpAdapter.makeDiskObject();
        }
        /// <name>
        /// destractor with out parameters
        /// </name>
        /// <summary>
        /// destractor with out parameters-The role of this function to destroy an object of this type automatically at the appropriate moment.
        /// </summary>
        ~Disk()
        {
            if (myDiskPointer != null)
                cppToCsharpAdapter.deleteDiskObject(ref myDiskPointer);
        }


        public VolumeHeader GetVolumeHeader()
        {
            try
            {

                VolumeHeader v = new VolumeHeader();
                int structSize = Marshal.SizeOf(v.GetType()); //Marshal.SizeOf(typeof(Student)); 
                IntPtr buffer = Marshal.AllocHGlobal(structSize);
                Marshal.StructureToPtr(v, buffer, true);

                // ... send buffer to dll
                cppToCsharpAdapter.getVolumeHeader(this.myDiskPointer, buffer);
                Marshal.PtrToStructure(buffer, v);

                // free allocate
                Marshal.FreeHGlobal(buffer);

                return v;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public DirEntry GetDirEntry(bool p,int i)
        {
            try
            {

                DirEntry d = new DirEntry();
                int structSize = Marshal.SizeOf(d.GetType());
                IntPtr buffer = Marshal.AllocHGlobal(structSize);
                Marshal.StructureToPtr(d, buffer, true);

                // ... send buffer to dll
                cppToCsharpAdapter.GetEntry(this.myDiskPointer, buffer, p, i);
                Marshal.PtrToStructure(buffer, d);

                // free allocate
                Marshal.FreeHGlobal(buffer);

                return d;
            }
            catch (SEHException )
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        /// <name>
        /// createdisk-2 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to create a virtual disk(unmounted)
        /// </summary>
        /// <param name="DiskName">Name of disk</param>
        /// <param name="OwnerName">The name of the owner</param>
        public void Createdisk(string diskName, string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.createdisk(this.myDiskPointer, diskName, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        /// <name>
        /// mountdisk-1 parameters
        /// </name>
        /// <summary>
        /// The role of this function-open the file who exercises the virtual disk
        /// </summary>
        /// <param name="diskName">Name of disk</param>
        public void Mountdisk(string diskName)
        {
            try
            {
                cppToCsharpAdapter.mountdisk(this.myDiskPointer, diskName);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        /// <name>
        /// unmountdisk-0 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to update all the sectors that contain structural information of the virtual disk,
        /// close the file of the virtual disk and to compare field mounted the value false
        /// </summary>
        public void Unmountdisk()
        {
            try
            {
                cppToCsharpAdapter.unmountdisk(this.myDiskPointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        /// <name>
        /// recreatedisk-1 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to reboot the virtual disk
        /// </summary>
        /// <param name="diskowner">The name of the owner</param>
        public void Recreatedisk(string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.recreatedisk(this.myDiskPointer, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }



        // Level 1
        /// <name>
        /// format-1 parameters
        /// </name>
        /// <summary>
        /// The role of this function to format a virtual disk
        /// </summary>
        /// <param name="OwnerName">The name of the owner</param>
        public void Format(string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.format(this.myDiskPointer, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        /// <name>
        /// howmuchempty-0 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to calculate the total number of Free clusters from the virtual disk
        /// </summary>
        /// <return>the total number of Free clusters</return>
        public int Howmuchempty()
        {
            try
            {
                return cppToCsharpAdapter.howmuchempty(this.myDiskPointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        //Level 2
        /// <name>
        /// createfile-9 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to make the creation of a data file
        /// </summary>
        /// <param name="FileName">The name of the file</param>
        /// <param name="OwnerName">The name of the owner</param>
        /// <param name="fileType">Determines the file type ("F" - records with fixed length; "V" - records with variable length)</param>
        /// <param name="RecLength">Record length</param>
        /// <param name="numSectorNeeded">Number of sectors requested</param>
        /// <param name="keyType">Data type of the key</param>/// <param name="Fat">File Allocation Table</param>
        /// <param name="OffsetKey">The offset of the start key in the record</param>
        /// <param name="keyLength">Key length</param>
        /// <param name="algoType">algorithm type for allcation  0  –  first fit, 1  –  best fit, 2  –  worst fit</param>
        public void Createfile(string fileName, string fileOwner, string FinalOrVar,
                                uint recSize, uint fileSize,
                                string keyType, uint keyOffset, uint keySize = 4, uint algoType=0)
        {
            try
            {
                cppToCsharpAdapter.createfile(this.myDiskPointer, fileName, fileOwner, FinalOrVar,
                              recSize, fileSize,
                                keyType, keyOffset, keySize,algoType);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        /// <name>
        /// delfile-2 parameters
        /// </name>
        /// <summary>
        /// The role of this function deletion of an existing file
        /// </summary>
        /// <param name="FileName">The name of the file</param>
        /// <param name="OwnerName">The name of the owner</param>
        public void Delfile(string fileName, string fileOwner)
        {
            try
            {
                cppToCsharpAdapter.delfile(this.myDiskPointer, fileName, fileOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        /// <name>
        /// extendfile-4 parameters
        /// </name>
        /// <summary>
        /// The role of this function to add space to an existing file
        /// </summary>
        /// <param name="FileName">The name of the file</param>
        /// <param name="OwnerName">The name of the owner</param>
        /// <param name="numSectorNeeded">Number of sectors requested</param>
        /// <param name="algoType">algorithm type for allcation  0  –  first fit, 1  –  best fit, 2  –  worst fit</param>
        public void Extendfile(string fileName, string fileOwner, uint size, uint algoType)
        {
            try
            {
                cppToCsharpAdapter.extendfile(this.myDiskPointer, fileName, fileOwner, size, algoType);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        // Level 3
        /// <name>
        /// openfile-3 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to Open a file
        /// </summary>
        /// <param name="FileName">The name of the file</param>
        /// <param name="userName">Name of user who opened the file</param>
        /// <param name="openType">How to open (input - "I", O - "O", I / O - "IO", added - "E")</param>
        /// <return>A pointer to an object of type FCB that function dynamically creates and initializes it according to parameter values ​​obtained</return>
        public FCB Openfile(string fileName, string fileOwner, string openMode)
        {
            try
            {
                IntPtr p = cppToCsharpAdapter.openfile(this.myDiskPointer, fileName, fileOwner, openMode);
                return new FCB(p);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
    }
}
