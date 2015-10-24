// Dlg_Compile.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_Compile.h"
#include ".\dlg_compile.h"


extern UINT WM_CLK_TREE;

// CDlg_Compile 对话框

IMPLEMENT_DYNCREATE(CDlg_Compile, CDialog)

CDlg_Compile::CDlg_Compile(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_Compile::IDD, pParent),
m_bIsLoad(FALSE),
m_nTreePage(-1)
{
}

CDlg_Compile::~CDlg_Compile()
{
}

BEGIN_MESSAGE_MAP(CDlg_Compile, CDialog)
    ON_CONTROL_RANGE(CBN_SETFOCUS, IDC_COMPLIE_COMBO0, IDC_COMPLIE_COMBO17, OnCbnSetfocusCompileCombo)
    ON_REGISTERED_MESSAGE(WM_CLK_TREE,      OnClickTree)
    ON_BN_CLICKED(IDC_COMPLIE_BTN_SAVE,     OnBnClickedComplieBtnSave)
    ON_BN_CLICKED(IDC_COMPLIE_BTN_OPEN,     OnBnClickedComplieBtnOpen)
    ON_BN_CLICKED(IDC_COMPLIE_BTN_CREATE,   OnBnClickedComplieBtnCreate)
    ON_BN_CLICKED(IDC_COMPLIE_BTN_MAKE,     OnBnClickedComplieBtnMake)
END_MESSAGE_MAP()

void CDlg_Compile::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Control(pDX,IDC_COMPLIE_TREE,       m_treRoom);
    DDX_Control(pDX,IDC_COMPLIE_COMBO_CFG,  m_cbbConfig);
    DDX_Control(pDX,IDC_COMPLIE_INFO,       m_staInfo);

    DDX_Control(pDX,IDC_COMPLIE_NAME0,      m_staName[0]);
    DDX_Control(pDX,IDC_COMPLIE_NAME1,      m_staName[1]);
    DDX_Control(pDX,IDC_COMPLIE_NAME2,      m_staName[2]);
    DDX_Control(pDX,IDC_COMPLIE_NAME3,      m_staName[3]);
    DDX_Control(pDX,IDC_COMPLIE_NAME4,      m_staName[4]);
    DDX_Control(pDX,IDC_COMPLIE_NAME5,      m_staName[5]);
    DDX_Control(pDX,IDC_COMPLIE_NAME6,      m_staName[6]);
    DDX_Control(pDX,IDC_COMPLIE_NAME7,      m_staName[7]);
    DDX_Control(pDX,IDC_COMPLIE_NAME8,      m_staName[8]);
    DDX_Control(pDX,IDC_COMPLIE_NAME9,      m_staName[9]);
    DDX_Control(pDX,IDC_COMPLIE_NAME10,     m_staName[10]);
    DDX_Control(pDX,IDC_COMPLIE_NAME11,     m_staName[11]);
    DDX_Control(pDX,IDC_COMPLIE_NAME12,     m_staName[12]);
    DDX_Control(pDX,IDC_COMPLIE_NAME13,     m_staName[13]);
    DDX_Control(pDX,IDC_COMPLIE_NAME14,     m_staName[14]);
    DDX_Control(pDX,IDC_COMPLIE_NAME15,     m_staName[15]);
    DDX_Control(pDX,IDC_COMPLIE_NAME16,     m_staName[16]);
    DDX_Control(pDX,IDC_COMPLIE_NAME17,     m_staName[17]);

    DDX_Control(pDX,IDC_COMPLIE_COMBO0,     m_cbbData[0]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO1,     m_cbbData[1]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO2,     m_cbbData[2]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO3,     m_cbbData[3]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO4,     m_cbbData[4]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO5,     m_cbbData[5]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO6,     m_cbbData[6]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO7,     m_cbbData[7]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO8,     m_cbbData[8]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO9,     m_cbbData[9]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO10,    m_cbbData[10]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO11,    m_cbbData[11]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO12,    m_cbbData[12]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO13,    m_cbbData[13]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO14,    m_cbbData[14]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO15,    m_cbbData[15]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO16,    m_cbbData[16]);
    DDX_Control(pDX,IDC_COMPLIE_COMBO17,    m_cbbData[17]);

}

BOOL CDlg_Compile::OnInitDialog()
{
    CDialog::OnInitDialog();

    //m_treRoom.SetImageList(g_ProFile.GetImageList(), TVSIL_NORMAL);

    int nIndex = 1;

    HTREEITEM Node[15] = {0};

    Node[0] = m_treRoom.AddNode(TVI_ROOT, _T("通用属性"), nIndex, 0);
    Node[3] = m_treRoom.AddNode(Node[0], _T("引用"), nIndex++, 0);

    Node[1] = m_treRoom.AddNode(TVI_ROOT, _T("配置属性"), nIndex, 0);
    Node[4] = m_treRoom.AddNode(Node[1], _T("常规"), nIndex++, 0);
    //Node[4] = m_treRoom.AddNode(Node[1], _T("调试"), nIndex++, 0);

    Node[2] = m_treRoom.AddNode(TVI_ROOT, _T("文件属性"), nIndex, 0);
    Node[5] = m_treRoom.AddNode(Node[2], _T("常规"), nIndex, 0);    

    Node[6] = m_treRoom.AddNode(Node[1], _T("C/C++"), nIndex, 0);
    m_treRoom.AddNode(Node[6], _T("常规"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("优化"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("预处理器"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("代码生成"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("语言"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("预编译头"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("输出文件"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("浏览信息"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("高级"), nIndex++, 0);
    m_treRoom.AddNode(Node[6], _T("命令行"), nIndex++, 0);

    Node[7] = m_treRoom.AddNode(Node[1], _T("链接器"), nIndex, 0);
    m_treRoom.AddNode(Node[7], _T("常规"), nIndex++, 0);
    m_treRoom.AddNode(Node[7], _T("输入"), nIndex++, 0);
    m_treRoom.AddNode(Node[7], _T("清单文件"), nIndex++, 0);
    m_treRoom.AddNode(Node[7], _T("调试"), nIndex++, 0);
    m_treRoom.AddNode(Node[7], _T("系统"), nIndex++, 0);
    m_treRoom.AddNode(Node[7], _T("优化"), nIndex++, 0);
    m_treRoom.AddNode(Node[7], _T("嵌入的IDL"), nIndex++, 0);
    m_treRoom.AddNode(Node[7], _T("高级"), nIndex++, 0);
    m_treRoom.AddNode(Node[7], _T("命令行"), nIndex++, 0);

    Node[8] = m_treRoom.AddNode(Node[1], _T("清单工具"), nIndex, 0);
    m_treRoom.AddNode(Node[8], _T("常规"), nIndex++, 0);
    m_treRoom.AddNode(Node[8], _T("输入和输出"), nIndex++, 0);
    m_treRoom.AddNode(Node[8], _T("独立COM"), nIndex++, 0);
    m_treRoom.AddNode(Node[8], _T("高级"), nIndex++, 0);
    m_treRoom.AddNode(Node[8], _T("命令行"), nIndex++, 0);

    Node[9] = m_treRoom.AddNode(Node[1], _T("资源"),nIndex, 0);
    m_treRoom.AddNode(Node[9], _T("常规"), nIndex++, 0);
    m_treRoom.AddNode(Node[9], _T("命令行"), nIndex++, 0);

    Node[10] = m_treRoom.AddNode(Node[1], _T("XML文档生成"), nIndex, 0);
    m_treRoom.AddNode(Node[10], _T("常规"), nIndex++, 0);
    m_treRoom.AddNode(Node[10], _T("命令行"), nIndex++, 0);

    Node[11] = m_treRoom.AddNode(Node[1], _T("浏览信息"), nIndex, 0);
    m_treRoom.AddNode(Node[11], _T("常规"), nIndex++, 0);
    m_treRoom.AddNode(Node[11], _T("命令行"), nIndex++, 0);

    Node[12] = m_treRoom.AddNode(Node[1], _T("生成事件"), nIndex, 0);
    m_treRoom.AddNode(Node[12], _T("预生成事件"), nIndex++, 0);
    m_treRoom.AddNode(Node[12], _T("预链接事件"), nIndex++, 0);
    m_treRoom.AddNode(Node[12], _T("生成后事件"), nIndex++, 0);

    Node[13] = m_treRoom.AddNode(Node[1], _T("自定义生成步骤"), nIndex, 0);
    m_treRoom.AddNode(Node[13], _T("常规"), nIndex++, 0);

    Node[14] = m_treRoom.AddNode(Node[1], _T("WEB部署"), nIndex, 0);
    m_treRoom.AddNode(Node[14], _T("常规"), nIndex++, 0); 

    m_treRoom.Expand(Node[0], TVE_EXPAND);
    m_treRoom.Expand(Node[1], TVE_EXPAND);
    m_treRoom.Expand(Node[2], TVE_EXPAND);
    m_treRoom.SelectItem(Node[3]);

    //------------------------------------------------------
    this->SelNewPage(1);
    //------------------------------------------------------

    return TRUE;
}

// 点击TreeCtrl
LRESULT CDlg_Compile::OnClickTree(WPARAM wParam, LPARAM lParam)
{
    this->SelNewPage((int)lParam);
    return 0;
}

// 点击ComboBox
void CDlg_Compile::OnCbnSetfocusCompileCombo(UINT nIndex)
{
    //m_staInfo.SetWindowText(m_xmlComplie.GetExplain(m_nTreePage, nIndex-IDC_COMPLIE_COMBO0));
}

// "应用"按钮
void CDlg_Compile::OnBnClickedComplieBtnSave()
{
    CString strSelect;
    CString strValues;
    CStringArray arValue;
    CStringArray arSelect;

    int nCfg = m_cbbConfig.GetCurSel();

    if (-1 != nCfg)
    {
        int nUse = nCfg + 1;
        int nCount = 0;//m_xmlComplie.GetAttribCount(m_nTreePage);

        for (int i = 0; i < nCount; i++)
        {
            int nItemCount = m_cbbData[i].GetCount();
            int nSel = m_cbbData[i].GetCurSel();

//             strSelect = m_xmlComplie.GetSelect(m_nTreePage, i);     // 读存可选项
//             strValues = m_xmlComplie.GetXmlValue(m_nTreePage, i);   // 读存数据
//             m_xmlComplie.CStringToArray(strValues, arValue);
//             m_xmlComplie.CStringToArray(strSelect, arSelect);

            if (1 == nItemCount)    // 只有一个的是Edit类型的
            {
                m_cbbData[i].GetWindowText(arValue[nUse]);
            }
            else if (nSel == nItemCount-1)   // 选中<从项目默认设置继承>,显示为默认值
            {
                arValue[nUse] = arValue[0];

                if (_T("true") == arValue[0])
                {
                    for (int j = 0; j < arSelect.GetCount(); j++)
                    {
                        if ((_T("是") == arSelect[j].Left(2)) || (_T("否") != arSelect[j].Left(2)))
                        {
                            nSel = j;
                            break;
                        }
                    }
                }
                else if (_T("false") == arValue[0])
                {
                    for (int j = 0; j < arSelect.GetCount(); j++)
                    {
                        if ((_T("否") == arSelect[j].Left(2)) || (_T("是") != arSelect[j].Left(2)))
                        {
                            nSel = j;
                            break;
                        }
                    }
                }
                else
                {
                    nSel = atoi(arValue[0]);
                }

                m_cbbData[i].SetCurSel(nSel);
            }
            else if (3 == nItemCount)   // 是|否|<从项目默认设置继承> 类型，但没选中
            {
                arValue[nUse] = (0 == nSel) ? _T("true") : _T("true");
            }
            else
            {
                arValue[nUse].Format(_T("%d"), nSel);
            }

            strValues = _T("");
            for (int j = 0; j < arValue.GetCount(); j++)
            {
                strValues += _T("|") + arValue[j];
            }

 //           m_xmlComplie.SetXmlValue(m_nTreePage, i, strValues);    // 写出新数据
        }
    }
}

// "打开vcproj"按钮
void CDlg_Compile::OnBnClickedComplieBtnOpen()
{
    CStringArray saConfig;
    CStringArray saPlatform;

    CString strCaption;
    CString strTemp = this->GetProjectFileName();

    if (_T("") != strTemp)
    {
        this->CleanConfig();
// 
//         if (m_xmlComplie.OpenVcProj(strTemp))
//         {
//             m_xmlComplie.GetConfigs(saConfig, TRUE);
// 
//             for (int i = 0; i < saConfig.GetCount(); i++)
//             {
//                 m_cbbConfig.InsertString(i, saConfig[i]);
//             }
// 
//             m_cbbConfig.SetCurSel(0);
// 
//             this->SelNewPage(1);
//         }
    }
}

// "创建vcproj"按钮
void CDlg_Compile::OnBnClickedComplieBtnCreate()
{
    CString strPathFile = this->GetProjectFileName();

    if (_T("") != strPathFile)
    {
        if (-1 == strPathFile.Find(_T(".vcproj")))
        {
            strPathFile += _T(".vcproj");
        }

        //m_xmlComplie.CreateVcProj(strPathFile);
    }
}

// "生成make"按钮
void CDlg_Compile::OnBnClickedComplieBtnMake()
{
}

// 打开一个选择文件窗体，然后选择一个文件
CString CDlg_Compile::GetProjectFileName(void)
{
    CFileDialog FileDlg(TRUE, NULL, NULL, NULL, _T("VC项目(*.vcproj)|*.vcproj|所有文件(*.*)|*.*||"));

    if (FileDlg.DoModal())
    {
        return FileDlg.GetPathName();
    }
    else
    {
        return CString(_T(""));
    }
}

// 选择一个新的页
void CDlg_Compile::SelNewPage(int nNewPage)
{
    if (m_nTreePage != nNewPage)
    {
        m_nTreePage = nNewPage;

        int nUse = m_cbbConfig.GetCurSel() + 1;
        int nCount = 0;//m_xmlComplie.GetAttribCount(m_nTreePage);

        for (int i = 0; i < nCount; i++)
        {
//             m_staName[i].SetWindowText(m_xmlComplie.GetName(m_nTreePage, i));
// 
//             this->SetComboData(i, m_xmlComplie.GetSelect(m_nTreePage, i), m_xmlComplie.GetXmlValue(m_nTreePage, i), nUse);

            m_staName[i].ShowWindow(SW_SHOW);
            m_cbbData[i].ShowWindow(SW_SHOW);
        }

        for (int i = 17; i >= nCount; i--)
        {
            m_staName[i].ShowWindow(SW_HIDE);
            m_cbbData[i].ShowWindow(SW_HIDE);
        }

//        m_staInfo.SetWindowText(m_xmlComplie.GetExplain(m_nTreePage, 0));
    }
}

// 设置ComboBox控件的数据
void CDlg_Compile::SetComboData(int nIndex, CString strSelect, CString strValue, int nUse)
{
    this->CleanComboData(nIndex);

    CStringArray arrValue;
    CStringArray arrSelect;

//     m_xmlComplie.CStringToArray(strValue, arrValue);
//     m_xmlComplie.CStringToArray(strSelect, arrSelect);

    int nValCount = (int)arrValue.GetCount();
    int nSelCount = (int)arrSelect.GetCount();

    if (0 == nSelCount)
    {
        if ((nValCount != 0) && (nUse >= 0) && (nUse < nValCount))
        {
            m_cbbData[nIndex].InsertString(0, arrValue[nUse]);
            m_cbbData[nIndex].SetCurSel(0);
        }
    }
    else
    {
        int i = 0;
        for (; i < nSelCount; i++)
        {
            m_cbbData[nIndex].InsertString(i, arrSelect[i]);
        }

        m_cbbData[nIndex].InsertString(i, _T("<从项目默认设置继承>"));

        CString strTemp = arrValue[nUse];
        int nSel = 0;

        if (_T("true") == strTemp)
        {
            for (int i = 0; i < arrSelect.GetCount(); i++)
            {
                if ((_T("是") == arrSelect[i].Left(2)) || (_T("否") != arrSelect[i].Left(2)))
                {
                    nSel = i;
                    break;
                }
            }
        }
        else if (_T("false") == strTemp)
        {
            for (int i = 0; i < arrSelect.GetCount(); i++)
            {
                if ((_T("否") == arrSelect[i].Left(2)) || (_T("是") != arrSelect[i].Left(2)))
                {
                    nSel = i;
                    break;
                }
            }
        }
        else
        {
            nSel = atoi(strTemp);
        }

        m_cbbData[nIndex].SetCurSel(nSel);
    }
}

// 清空ComboBox控件的数据
void CDlg_Compile::CleanComboData(int nIndex)
{
    int nCount = m_cbbData[nIndex].GetCount();
    for (int i = 0; i < nCount; i++)
    {
        m_cbbData[nIndex].DeleteString(0);
    }
}

// 清空配置ComboBox
void CDlg_Compile::CleanConfig(void)
{
    int nCount = m_cbbConfig.GetCount();
    for (int i = 0; i < nCount; i++)
    {
        m_cbbConfig.DeleteString(0);
    }
}
