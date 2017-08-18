#include <Windows.h>
#include "GsHelper.h"
#include <iostream>
#include <assert.h>

using namespace std;
CGsHelper& CGsHelper::getInstance()
{
    static CGsHelper gs;

    return gs;
}

CGsHelper::CGsHelper()
    : m_hdll(nullptr)
{
    
}


CGsHelper::~CGsHelper()
{
    if (m_hdll == nullptr)
        FreeLibrary(m_hdll);
}

bool CGsHelper::loadDll(const std::string& dllURI)
{
    if (m_hdll == nullptr)
        m_hdll = LoadLibrary(dllURI.data());
    if (!m_hdll)
        return false;

    gsdll_revision = (PFN_gsdll_revision)GetProcAddress(m_hdll, "gsdll_revision");
    assert(gsdll_revision, "function load failed: gsdll_revision");
    gsdll_init = (PFN_gsdll_init)GetProcAddress(m_hdll, "gsdll_init");
    assert(gsdll_init, "function load failed: gsdll_init");
    gsdll_execute_begin = (PFN_gsdll_execute_begin)GetProcAddress(m_hdll, "gsdll_execute_begin");
    assert(gsdll_execute_begin, "function load failed: gsdll_execute_begin");
    gsdll_execute_cont = (PFN_gsdll_execute_cont)GetProcAddress(m_hdll, "gsdll_execute_cont");
    assert(gsdll_execute_cont, "function load failed: gsdll_execute_cont");
    gsdll_execute_end = (PFN_gsdll_execute_end)GetProcAddress(m_hdll, "gsdll_execute_end");
    assert(gsdll_execute_end, "function load failed: gsdll_execute_end");
    gsdll_exit = (PFN_gsdll_exit)GetProcAddress(m_hdll, "gsdll_exit");
    assert(gsdll_exit, "function load failed: gsdll_exit");
    gsdll_lock_device = (PFN_gsdll_lock_device)GetProcAddress(m_hdll, "gsdll_lock_device");
    assert(gsdll_lock_device, "function load failed: gsdll_lock_device");


    gsapi_revision = (PFN_gsapi_revision)GetProcAddress(m_hdll, "gsapi_revision");
    assert(gsapi_revision, "function load failed: gsapi_revision");
    gsapi_new_instance = (PFN_gsapi_new_instance)GetProcAddress(m_hdll, "gsapi_new_instance");
    assert(gsapi_new_instance, "function load failed: gsapi_new_instance");
    gsapi_delete_instance = (PFN_gsapi_delete_instance)GetProcAddress(m_hdll, "gsapi_delete_instance");
    assert(gsapi_delete_instance, "function load failed: gsapi_delete_instance");
    gsapi_set_stdio = (PFN_gsapi_set_stdio)GetProcAddress(m_hdll, "gsapi_set_stdio");
    assert(gsapi_set_stdio, "function load failed: gsapi_set_stdio");
    gsapi_set_poll = (PFN_gsapi_set_poll)GetProcAddress(m_hdll, "gsapi_set_poll");
    assert(gsapi_set_poll, "function load failed: gsapi_set_poll");
    gsapi_set_display_callback = (PFN_gsapi_set_display_callback)GetProcAddress(m_hdll, "gsapi_set_display_callback");
    assert(gsapi_set_display_callback, "function load failed: gsapi_set_display_callback");
    gsapi_init_with_args = (PFN_gsapi_init_with_args)GetProcAddress(m_hdll, "gsapi_init_with_args");
    assert(gsapi_init_with_args, "function load failed: gsapi_init_with_args");
    gsapi_run_string_begin = (PFN_gsapi_run_string_begin)GetProcAddress(m_hdll, "gsapi_run_string_begin");
    assert(gsapi_run_string_begin, "function load failed: gsapi_run_string_begin");
    gsapi_run_string_continue = (PFN_gsapi_run_string_continue)GetProcAddress(m_hdll, "gsapi_run_string_continue");
    assert(gsapi_run_string_continue, "function load failed: gsapi_run_string_continue");
    gsapi_run_string_end = (PFN_gsapi_run_string_end)GetProcAddress(m_hdll, "gsapi_run_string_end");
    assert(gsapi_run_string_end, "function load failed: gsapi_run_string_end");
    gsapi_run_string_with_length = (PFN_gsapi_run_string_with_length)GetProcAddress(m_hdll, "gsapi_run_string_with_length");
    assert(gsapi_run_string_with_length, "function load failed: gsapi_run_string_with_length");
    gsapi_run_string = (PFN_gsapi_run_string)GetProcAddress(m_hdll, "gsapi_run_string");
    assert(gsapi_run_string, "function load failed: gsapi_run_string");
    gsapi_run_file = (PFN_gsapi_run_file)GetProcAddress(m_hdll, "gsdll_revision");
    assert(gsapi_run_file, "function load failed: gsapi_run_file");
    gsapi_exit = (PFN_gsapi_exit)GetProcAddress(m_hdll, "gsapi_exit");
    assert(gsapi_exit, "function load failed: gsapi_exit");
    gsapi_set_visual_tracer = (PFN_gsapi_set_visual_tracer)GetProcAddress(m_hdll, "gsapi_set_visual_tracer");
    assert(gsapi_set_visual_tracer, "function load failed: gsapi_set_visual_tracer");

    gsdll_copy_dib = (PFN_gsdll_copy_dib)GetProcAddress(m_hdll, "gsdll_copy_dib");;
    assert(gsdll_copy_dib, "function load failed: gsdll_copy_dib");
    gsdll_copy_palette = (PFN_gsdll_copy_palette)GetProcAddress(m_hdll, "gsdll_copy_palette");;
    assert(gsdll_copy_palette, "function load failed: gsdll_copy_palette");
    gsdll_draw = (PFN_gsdll_draw)GetProcAddress(m_hdll, "gsdll_draw");;
    assert(gsdll_draw, "function load failed: gsdll_draw");
    gsdll_get_bitmap_row = (PFN_gsdll_get_bitmap_row)GetProcAddress(m_hdll, "gsdll_get_bitmap_row");;
    assert(gsdll_get_bitmap_row, "function load failed: gsdll_get_bitmap_row");

    return true;
}

void CGsHelper::printGsRevision()
{
    const char* product;
    const char* copyright;
    long revision;
    long revisionDate;
    gsdll_revision(&product, &copyright, &revision, &revisionDate);

    cout << "product : " << product << ", copy right: " << copyright << ", revision = " << revision << ", revisionDate = " << revisionDate << endl;
}


void CGsHelper::Convert(std::string inputFile, std::string outputFile, int firstPage, int lastPage, std::string deviceFormat, int width, int height)
{
// http://blog.csdn.net/ljsspace/article/details/6530046    
    //string[] sArgs = GetGeneratedArgs(inputFile, outputFile,

    gs_main_instance *ins;
    int intReturn = gsapi_new_instance(&ins, nullptr);
    cout << "return = " << intReturn << endl;
    //intReturn = gsapi_init_with_args(ins, intElementCount, intptrArgs);

    //gsapi_exit(intGSInstanceHandle);
    //gsapi_delete_instance(intGSInstanceHandle);
}

//string GetGeneratedArgs(string inputFile, string outputFile, int firstPage, int lastPage, string deviceFormat, int width, int height)
//{
//    this._sDeviceFormat = deviceFormat;
//    this._iResolutionX = width;
//    this._iResolutionY = height;
//    // Count how many extra args are need - HRangel - 11/29/2006, 3:13:43 PM  
//    ArrayList lstExtraArgs = new ArrayList();
//    if (_sDeviceFormat == "jpg" && _iJPEGQuality > 0 && _iJPEGQuality < 101)
//        lstExtraArgs.Add("-dJPEGQ=" + _iJPEGQuality);
//    if (_iWidth > 0 && _iHeight > 0)
//        lstExtraArgs.Add("-g" + _iWidth + "x" + _iHeight);
//    if (_bFitPage)
//        lstExtraArgs.Add("-dPDFFitPage");
//    if (_iResolutionX > 0)
//    {
//        if (_iResolutionY > 0)
//            lstExtraArgs.Add("-r" + _iResolutionX + "x" + _iResolutionY);
//        else
//            lstExtraArgs.Add("-r" + _iResolutionX);
//    }
//    // Load Fixed Args - HRangel - 11/29/2006, 3:34:02 PM  
//    int iFixedCount = 17;
//    int iExtraArgsCount = lstExtraArgs.Count;
//    string[] args = new string[iFixedCount + lstExtraArgs.Count];
//    /*
//    // Keep gs from writing information to standard output
//    "-q",
//    "-dQUIET",
//
//    "-dPARANOIDSAFER", // Run this command in safe mode
//    "-dBATCH", // Keep gs from going into interactive mode
//    "-dNOPAUSE", // Do not prompt and pause for each page
//    "-dNOPROMPT", // Disable prompts for user interaction
//    "-dMaxBitmap=500000000", // Set high for better performance
//
//    // Set the starting and ending pages
//    String.Format("-dFirstPage={0}", firstPage),
//    String.Format("-dLastPage={0}", lastPage),
//
//    // Configure the output anti-aliasing, resolution, etc
//    "-dAlignToPixels=0",
//    "-dGridFitTT=0",
//    "-sDEVICE=jpeg",
//    "-dTextAlphaBits=4",
//    "-dGraphicsAlphaBits=4",
//    */
//    args[0] = "pdf2img";//this parameter have little real use  
//    args[1] = "-dNOPAUSE";//I don't want interruptions  
//    args[2] = "-dBATCH";//stop after  
//                        //args[3]="-dSAFER";  
//    args[3] = "-dPARANOIDSAFER";
//    args[4] = "-sDEVICE=" + _sDeviceFormat;//what kind of export format i should provide  
//    args[5] = "-q";
//    args[6] = "-dQUIET";
//    args[7] = "-dNOPROMPT";
//    args[8] = "-dMaxBitmap=500000000";
//    args[9] = String.Format("-dFirstPage={0}", firstPage);
//    args[10] = String.Format("-dLastPage={0}", lastPage);
//    args[11] = "-dAlignToPixels=0";
//    args[12] = "-dGridFitTT=0";
//    args[13] = "-dTextAlphaBits=4";
//    args[14] = "-dGraphicsAlphaBits=4";
//    //For a complete list watch here:  
//    //http://pages.cs.wisc.edu/~ghost/doc/cvs/Devices.htm  
//    //Fill the remaining parameters  
//    for (int i = 0; i < iExtraArgsCount; i++)
//    {
//        args[15 + i] = (string)lstExtraArgs[i];
//    }
//    //Fill outputfile and inputfile  
//    args[15 + iExtraArgsCount] = string.Format("-sOutputFile={0}", outputFile);
//    args[16 + iExtraArgsCount] = string.Format("{0}", inputFile);
//    return args;
//}