
void CMsgTestDlg::OnClose()
{
    HWND hWnd = ::FindWindow("Notepad", NULL);
    if (hWnd == NULL)
    {
        AfxMessageBox("没有找到记事本");
        return;
    }
}