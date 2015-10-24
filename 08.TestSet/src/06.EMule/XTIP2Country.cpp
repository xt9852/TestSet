
// eMule SVN  http://easymule.googlecode.com/svn/trunk/

#include "StdAfx.h"
#include "XTIP2Country.h"

UINT WM_IP2COUNTRY_NOTIFY = RegisterWindowMessage(_T("WM_IP2COUNTRY_NOTIFY"));

#define DEFAULT_COUNTRY                 0
#define NOFLAG_COUNTRY                  1

//------------------------------------------------------------------------------
#define IDI_COUNTRY_FLAG_AD             101
#define IDI_COUNTRY_FLAG_AE             102
#define IDI_COUNTRY_FLAG_AF             103
#define IDI_COUNTRY_FLAG_AG             104
#define IDI_COUNTRY_FLAG_AI             105
#define IDI_COUNTRY_FLAG_AL             106
#define IDI_COUNTRY_FLAG_AM             107
#define IDI_COUNTRY_FLAG_AN             108
#define IDI_COUNTRY_FLAG_AO             109
#define IDI_COUNTRY_FLAG_AR             110
#define IDI_COUNTRY_FLAG_AS             111
#define IDI_COUNTRY_FLAG_AT             112
#define IDI_COUNTRY_FLAG_AU             113
#define IDI_COUNTRY_FLAG_AW             114
#define IDI_COUNTRY_FLAG_AZ             115
#define IDI_COUNTRY_FLAG_BA             116
#define IDI_COUNTRY_FLAG_BB             117
#define IDI_COUNTRY_FLAG_BD             118
#define IDI_COUNTRY_FLAG_BE             119
#define IDI_COUNTRY_FLAG_BF             120
#define IDI_COUNTRY_FLAG_BG             121
#define IDI_COUNTRY_FLAG_BH             122
#define IDI_COUNTRY_FLAG_BI             123
#define IDI_COUNTRY_FLAG_BJ             124
#define IDI_COUNTRY_FLAG_BM             125
#define IDI_COUNTRY_FLAG_BN             126
#define IDI_COUNTRY_FLAG_BO             127
#define IDI_COUNTRY_FLAG_BR             128
#define IDI_COUNTRY_FLAG_BS             129
#define IDI_COUNTRY_FLAG_BT             130
#define IDI_COUNTRY_FLAG_BW             131
#define IDI_COUNTRY_FLAG_BY             132
#define IDI_COUNTRY_FLAG_BZ             133
#define IDI_COUNTRY_FLAG_CA             134
#define IDI_COUNTRY_FLAG_CC             135
#define IDI_COUNTRY_FLAG_CD             136
#define IDI_COUNTRY_FLAG_CF             137
#define IDI_COUNTRY_FLAG_CG             138
#define IDI_COUNTRY_FLAG_CH             139
#define IDI_COUNTRY_FLAG_CI             140
#define IDI_COUNTRY_FLAG_CK             141
#define IDI_COUNTRY_FLAG_CL             142
#define IDI_COUNTRY_FLAG_CM             143
#define IDI_COUNTRY_FLAG_CN             144
#define IDI_COUNTRY_FLAG_CO             145
#define IDI_COUNTRY_FLAG_CR             146
#define IDI_COUNTRY_FLAG_CU             147
#define IDI_COUNTRY_FLAG_CV             148
#define IDI_COUNTRY_FLAG_CX             149
#define IDI_COUNTRY_FLAG_CY             150
#define IDI_COUNTRY_FLAG_CZ             151
#define IDI_COUNTRY_FLAG_DE             152
#define IDI_COUNTRY_FLAG_DJ             153
#define IDI_COUNTRY_FLAG_DK             154
#define IDI_COUNTRY_FLAG_DM             155
#define IDI_COUNTRY_FLAG_DO             156
#define IDI_COUNTRY_FLAG_DZ             157
#define IDI_COUNTRY_FLAG_EC             158
#define IDI_COUNTRY_FLAG_EE             159
#define IDI_COUNTRY_FLAG_EG             160
#define IDI_COUNTRY_FLAG_EH             161
#define IDI_COUNTRY_FLAG_ER             162
#define IDI_COUNTRY_FLAG_ES             163
#define IDI_COUNTRY_FLAG_ET             164
#define IDI_COUNTRY_FLAG_FI             165
#define IDI_COUNTRY_FLAG_FJ             166
#define IDI_COUNTRY_FLAG_FK             167
#define IDI_COUNTRY_FLAG_FM             168
#define IDI_COUNTRY_FLAG_FO             169
#define IDI_COUNTRY_FLAG_FR             170
#define IDI_COUNTRY_FLAG_GA             171
#define IDI_COUNTRY_FLAG_GB             172
#define IDI_COUNTRY_FLAG_GD             173
#define IDI_COUNTRY_FLAG_GE             174
#define IDI_COUNTRY_FLAG_GG             175
#define IDI_COUNTRY_FLAG_GH             176
#define IDI_COUNTRY_FLAG_GI             177
#define IDI_COUNTRY_FLAG_GK             178
#define IDI_COUNTRY_FLAG_GL             179
#define IDI_COUNTRY_FLAG_GM             180
#define IDI_COUNTRY_FLAG_GN             181
#define IDI_COUNTRY_FLAG_GP             182
#define IDI_COUNTRY_FLAG_GQ             183
#define IDI_COUNTRY_FLAG_GR             184
#define IDI_COUNTRY_FLAG_GS             185
#define IDI_COUNTRY_FLAG_GT             186
#define IDI_COUNTRY_FLAG_GU             187
#define IDI_COUNTRY_FLAG_GW             188
#define IDI_COUNTRY_FLAG_GY             189
#define IDI_COUNTRY_FLAG_HK             190
#define IDI_COUNTRY_FLAG_HN             191
#define IDI_COUNTRY_FLAG_HR             192
#define IDI_COUNTRY_FLAG_HT             193
#define IDI_COUNTRY_FLAG_HU             194
#define IDI_COUNTRY_FLAG_ID             195
#define IDI_COUNTRY_FLAG_IE             196
#define IDI_COUNTRY_FLAG_IL             197
#define IDI_COUNTRY_FLAG_IM             198
#define IDI_COUNTRY_FLAG_IN             199
#define IDI_COUNTRY_FLAG_IO             200
#define IDI_COUNTRY_FLAG_IQ             201
#define IDI_COUNTRY_FLAG_IR             202
#define IDI_COUNTRY_FLAG_IS             203
#define IDI_COUNTRY_FLAG_IT             204
#define IDI_COUNTRY_FLAG_JE             205
#define IDI_COUNTRY_FLAG_JM             206
#define IDI_COUNTRY_FLAG_JO             207
#define IDI_COUNTRY_FLAG_JP             208
#define IDI_COUNTRY_FLAG_KE             209
#define IDI_COUNTRY_FLAG_KG             210
#define IDI_COUNTRY_FLAG_KH             211
#define IDI_COUNTRY_FLAG_KI             212
#define IDI_COUNTRY_FLAG_KM             213
#define IDI_COUNTRY_FLAG_KN             214
#define IDI_COUNTRY_FLAG_KP             215
#define IDI_COUNTRY_FLAG_KR             216
#define IDI_COUNTRY_FLAG_KW             217
#define IDI_COUNTRY_FLAG_KY             218
#define IDI_COUNTRY_FLAG_KZ             219
#define IDI_COUNTRY_FLAG_LA             220
#define IDI_COUNTRY_FLAG_LB             221
#define IDI_COUNTRY_FLAG_LC             222
#define IDI_COUNTRY_FLAG_LI             223
#define IDI_COUNTRY_FLAG_LK             224
#define IDI_COUNTRY_FLAG_LR             225
#define IDI_COUNTRY_FLAG_LS             226
#define IDI_COUNTRY_FLAG_LT             227
#define IDI_COUNTRY_FLAG_LU             228
#define IDI_COUNTRY_FLAG_LV             229
#define IDI_COUNTRY_FLAG_LY             230
#define IDI_COUNTRY_FLAG_MA             231
#define IDI_COUNTRY_FLAG_MC             232
#define IDI_COUNTRY_FLAG_MD             233
#define IDI_COUNTRY_FLAG_MG             234
#define IDI_COUNTRY_FLAG_MH             235
#define IDI_COUNTRY_FLAG_MK             236
#define IDI_COUNTRY_FLAG_ML             237
#define IDI_COUNTRY_FLAG_MM             238
#define IDI_COUNTRY_FLAG_MN             239
#define IDI_COUNTRY_FLAG_MO             240
#define IDI_COUNTRY_FLAG_MP             241
#define IDI_COUNTRY_FLAG_MQ             242
#define IDI_COUNTRY_FLAG_MR             243
#define IDI_COUNTRY_FLAG_MS             244
#define IDI_COUNTRY_FLAG_MT             245
#define IDI_COUNTRY_FLAG_MU             246
#define IDI_COUNTRY_FLAG_MV             247
#define IDI_COUNTRY_FLAG_MW             248
#define IDI_COUNTRY_FLAG_MX             249
#define IDI_COUNTRY_FLAG_MY             250
#define IDI_COUNTRY_FLAG_MZ             251
#define IDI_COUNTRY_FLAG_NA             252
#define IDI_COUNTRY_FLAG_NC             253
#define IDI_COUNTRY_FLAG_NE             254
#define IDI_COUNTRY_FLAG_NF             255
#define IDI_COUNTRY_FLAG_NG             256
#define IDI_COUNTRY_FLAG_NI             257
#define IDI_COUNTRY_FLAG_NL             258
#define IDI_COUNTRY_FLAG_NO             259
#define IDI_COUNTRY_FLAG_NP             260
#define IDI_COUNTRY_FLAG_NR             261
#define IDI_COUNTRY_FLAG_NU             262
#define IDI_COUNTRY_FLAG_NZ             263
#define IDI_COUNTRY_FLAG_OM             264
#define IDI_COUNTRY_FLAG_PA             265
#define IDI_COUNTRY_FLAG_PC             266
#define IDI_COUNTRY_FLAG_PE             267
#define IDI_COUNTRY_FLAG_PF             268
#define IDI_COUNTRY_FLAG_PG             269
#define IDI_COUNTRY_FLAG_PH             270
#define IDI_COUNTRY_FLAG_PK             271
#define IDI_COUNTRY_FLAG_PL             272
#define IDI_COUNTRY_FLAG_PM             273
#define IDI_COUNTRY_FLAG_PN             274
#define IDI_COUNTRY_FLAG_PR             275
#define IDI_COUNTRY_FLAG_PS             276
#define IDI_COUNTRY_FLAG_PT             277
#define IDI_COUNTRY_FLAG_PW             278
#define IDI_COUNTRY_FLAG_PY             279
#define IDI_COUNTRY_FLAG_QA             280
#define IDI_COUNTRY_FLAG_RO             281
#define IDI_COUNTRY_FLAG_RU             282
#define IDI_COUNTRY_FLAG_RW             283
#define IDI_COUNTRY_FLAG_SA             284
#define IDI_COUNTRY_FLAG_SB             285
#define IDI_COUNTRY_FLAG_SC             286
#define IDI_COUNTRY_FLAG_SD             287
#define IDI_COUNTRY_FLAG_SE             288
#define IDI_COUNTRY_FLAG_SG             289
#define IDI_COUNTRY_FLAG_SH             290
#define IDI_COUNTRY_FLAG_SI             291
#define IDI_COUNTRY_FLAG_SK             292
#define IDI_COUNTRY_FLAG_SL             293
#define IDI_COUNTRY_FLAG_SM             294
#define IDI_COUNTRY_FLAG_SN             295
#define IDI_COUNTRY_FLAG_SO             296
#define IDI_COUNTRY_FLAG_SR             297
#define IDI_COUNTRY_FLAG_ST             298
#define IDI_COUNTRY_FLAG_SU             299
#define IDI_COUNTRY_FLAG_SV             300
#define IDI_COUNTRY_FLAG_SY             301
#define IDI_COUNTRY_FLAG_SZ             302
#define IDI_COUNTRY_FLAG_TC             303
#define IDI_COUNTRY_FLAG_TD             304
#define IDI_COUNTRY_FLAG_TF             305
#define IDI_COUNTRY_FLAG_TG             306
#define IDI_COUNTRY_FLAG_TH             307
#define IDI_COUNTRY_FLAG_TJ             308
#define IDI_COUNTRY_FLAG_TK             309
#define IDI_COUNTRY_FLAG_TL             310
#define IDI_COUNTRY_FLAG_TM             311
#define IDI_COUNTRY_FLAG_TN             312
#define IDI_COUNTRY_FLAG_TO             313
#define IDI_COUNTRY_FLAG_TR             314
#define IDI_COUNTRY_FLAG_TT             315
#define IDI_COUNTRY_FLAG_TV             316
#define IDI_COUNTRY_FLAG_TW             317
#define IDI_COUNTRY_FLAG_TZ             318
#define IDI_COUNTRY_FLAG_UA             319
#define IDI_COUNTRY_FLAG_UG             320
#define IDI_COUNTRY_FLAG_UM             321
#define IDI_COUNTRY_FLAG_US             322
#define IDI_COUNTRY_FLAG_UY             323
#define IDI_COUNTRY_FLAG_UZ             324
#define IDI_COUNTRY_FLAG_VA             325
#define IDI_COUNTRY_FLAG_VC             326
#define IDI_COUNTRY_FLAG_VE             327
#define IDI_COUNTRY_FLAG_VG             328
#define IDI_COUNTRY_FLAG_VI             329
#define IDI_COUNTRY_FLAG_VN             330
#define IDI_COUNTRY_FLAG_VU             331
#define IDI_COUNTRY_FLAG_WF             332
#define IDI_COUNTRY_FLAG_WS             333
#define IDI_COUNTRY_FLAG_YE             334
#define IDI_COUNTRY_FLAG_YU             335
#define IDI_COUNTRY_FLAG_ZA             336
#define IDI_COUNTRY_FLAG_ZM             337
#define IDI_COUNTRY_FLAG_ZW             338
#define IDI_COUNTRY_FLAG_UK             340
#define IDI_COUNTRY_FLAG_CS             341
#define IDI_COUNTRY_FLAG_NOFLAG         342
#define IDI_COUNTRY_FLAG_EU             344

//------------------------------------------------------------------------------

CXTIP2Country::CXTIP2Country()
    :m_hWnd(NULL),
    m_pszFile(NULL),
    m_pRange(NULL),
    m_pCountry(NULL)
{
    m_strProvince = _T("中国全国首都\
北京天津上海重庆河北山西辽宁吉林黑龙江\
苏浙江安徽福建台湾江西山东河南湖北湖南广东海南四川贵州\
云南陕西甘肃青海内蒙广西西藏宁夏新疆香港澳门\
清华南开同济长江黄河中央对外汉中中山\
华中华东华南华北北方西北中北中南\
长城东南东华西华集美中科\
厦门宁波合肥成都武汉兰州郑州福州南昌暨南\
西安太原南京长沙青岛大连珠海\
乌鲁內蒙\
东北长春大庆哈尔佳木齐齐\
联通");

    UINT nThreadID = 0;
    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, IP2CountryThread, (void*)this, 0, &nThreadID);
    ::CloseHandle(hThread);
}

CXTIP2Country::~CXTIP2Country()
{
    m_IpRangeMap.RemoveAll();
    m_CountryMap.RemoveAll();

    if (NULL != m_pRange) delete[] m_pRange;
    if (NULL != m_pszFile) delete[] m_pszFile;
    if (NULL != m_pCountry) delete[] m_pCountry;
}

void CXTIP2Country::SetOwner(HWND hWnd)
{
    m_hWnd = hWnd;
}

void CXTIP2Country::GetCountryInfo(void)
{
    UINT nThreadID = 0;
    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, IP2CountryThread, (void*)this, 0, &nThreadID);
    ::CloseHandle(hThread);
}

unsigned CXTIP2Country::IP2CountryThread(LPVOID pthis)
{
    if (NULL == pthis)  return 1;

    CXTIP2Country* pThis = reinterpret_cast<CXTIP2Country*>(pthis);
    ASSERT(pThis);

    try
    {
        if (!pThis->LoadCountryFlagLib()) AfxMessageBox(_T("加载国旗DLL出错"));
        if (!pThis->LoadFromFile()) AfxMessageBox(_T("加载IP地址数据出错"));
    }
    catch (...)
    {
        TRACE(_T("CXTIP2Country::IP2CountryThread ErrorCode:%d"), ::GetLastError());
    }
    return 0;
}

bool CXTIP2Country::LoadCountryFlagLib()
{
    try
    {
        HINSTANCE hFlagDll = LoadLibrary(_T("res\\eMule\\countryflag.dll")); 
        if (NULL != hFlagDll) 
        {
            HICON iconHandle = NULL;
            m_CountryMap.RemoveAll();
            m_CountryFlagImageList.DeleteImageList();
            m_CountryFlagImageList.Create(18, 16, ILC_COLOR32 | ILC_MASK, 0, 1);
            m_CountryFlagImageList.SetBkColor(CLR_NONE);

            WORD resID[] = 
            {
                //first res in image list should be N/A
                    IDI_COUNTRY_FLAG_CN,

                    IDI_COUNTRY_FLAG_NOFLAG,    // 1
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,    // 5
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,    // 10
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,    // 15
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,    // 20
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,    // 25
                    IDI_COUNTRY_FLAG_NOFLAG,
                    IDI_COUNTRY_FLAG_NOFLAG,    // 27

                    IDI_COUNTRY_FLAG_US,        // 美国
                    IDI_COUNTRY_FLAG_IT,        // 意大利
                    IDI_COUNTRY_FLAG_CH,        // 瑞士
                    IDI_COUNTRY_FLAG_FR,        // 法国
                    IDI_COUNTRY_FLAG_FR,        // 法国
                    IDI_COUNTRY_FLAG_NL,        // 荷兰
                    IDI_COUNTRY_FLAG_NL,        // 荷兰
                    IDI_COUNTRY_FLAG_UK,        // 英国
                    IDI_COUNTRY_FLAG_FI,        // 芬兰

                    IDI_COUNTRY_FLAG_BD,        // 孟加拉国
                    IDI_COUNTRY_FLAG_BA,        // 波黑
                    IDI_COUNTRY_FLAG_AE,        // 阿拉伯联合酋长国
                    IDI_COUNTRY_FLAG_UK,        // 英国
                    IDI_COUNTRY_FLAG_PR,        // 波多黎各
                    IDI_COUNTRY_FLAG_RO,        // 罗马尼亚
                    IDI_COUNTRY_FLAG_KR,        // 韩国
                    IDI_COUNTRY_FLAG_JP,        // 日本
                    IDI_COUNTRY_FLAG_EU,        // 欧洲
                    IDI_COUNTRY_FLAG_FJ,        // 斐济
                    IDI_COUNTRY_FLAG_CA,        // 澳大利亚

                    IDI_COUNTRY_FLAG_US,
                    IDI_COUNTRY_FLAG_US,
                    IDI_COUNTRY_FLAG_US,
                    IDI_COUNTRY_FLAG_US,

                    IDI_COUNTRY_FLAG_CN,
                    IDI_COUNTRY_FLAG_CN,
                    IDI_COUNTRY_FLAG_CN,
                    IDI_COUNTRY_FLAG_CN,
                    IDI_COUNTRY_FLAG_CN,
                    IDI_COUNTRY_FLAG_CN,
                    IDI_COUNTRY_FLAG_CN,

                    IDI_COUNTRY_FLAG_AD, IDI_COUNTRY_FLAG_AE, IDI_COUNTRY_FLAG_AF, IDI_COUNTRY_FLAG_AG, 
                    IDI_COUNTRY_FLAG_AI, IDI_COUNTRY_FLAG_AL, IDI_COUNTRY_FLAG_AM, IDI_COUNTRY_FLAG_AN, 
                    IDI_COUNTRY_FLAG_AO, IDI_COUNTRY_FLAG_AR, IDI_COUNTRY_FLAG_AS, IDI_COUNTRY_FLAG_AT, 
                    IDI_COUNTRY_FLAG_AU, IDI_COUNTRY_FLAG_AW, IDI_COUNTRY_FLAG_AZ, IDI_COUNTRY_FLAG_BA, 
                    IDI_COUNTRY_FLAG_BB, IDI_COUNTRY_FLAG_BD, IDI_COUNTRY_FLAG_BE, IDI_COUNTRY_FLAG_BF, 
                    IDI_COUNTRY_FLAG_BG, IDI_COUNTRY_FLAG_BH, IDI_COUNTRY_FLAG_BI, IDI_COUNTRY_FLAG_BJ, 
                    IDI_COUNTRY_FLAG_BM, IDI_COUNTRY_FLAG_BN, IDI_COUNTRY_FLAG_BO, IDI_COUNTRY_FLAG_BR, 
                    IDI_COUNTRY_FLAG_BS, IDI_COUNTRY_FLAG_BT, IDI_COUNTRY_FLAG_BW, IDI_COUNTRY_FLAG_BY, 
                    IDI_COUNTRY_FLAG_BZ, IDI_COUNTRY_FLAG_CA, IDI_COUNTRY_FLAG_CC, IDI_COUNTRY_FLAG_CD, 
                    IDI_COUNTRY_FLAG_CF, IDI_COUNTRY_FLAG_CG, IDI_COUNTRY_FLAG_CH, IDI_COUNTRY_FLAG_CI, 
                    IDI_COUNTRY_FLAG_CK, IDI_COUNTRY_FLAG_CL, IDI_COUNTRY_FLAG_CM, IDI_COUNTRY_FLAG_CN, 
                    IDI_COUNTRY_FLAG_CO, IDI_COUNTRY_FLAG_CR, IDI_COUNTRY_FLAG_CU, IDI_COUNTRY_FLAG_CV, 
                    IDI_COUNTRY_FLAG_CX, IDI_COUNTRY_FLAG_CY, IDI_COUNTRY_FLAG_CZ, IDI_COUNTRY_FLAG_DE, 
                    IDI_COUNTRY_FLAG_DJ, IDI_COUNTRY_FLAG_DK, IDI_COUNTRY_FLAG_DM, IDI_COUNTRY_FLAG_DO, 
                    IDI_COUNTRY_FLAG_DZ, IDI_COUNTRY_FLAG_EC, IDI_COUNTRY_FLAG_EE, IDI_COUNTRY_FLAG_EG, 
                    IDI_COUNTRY_FLAG_EH, IDI_COUNTRY_FLAG_ER, IDI_COUNTRY_FLAG_ES, IDI_COUNTRY_FLAG_ET, 
                    IDI_COUNTRY_FLAG_FI, IDI_COUNTRY_FLAG_FJ, IDI_COUNTRY_FLAG_FK, IDI_COUNTRY_FLAG_FM, 
                    IDI_COUNTRY_FLAG_FO, IDI_COUNTRY_FLAG_FR, IDI_COUNTRY_FLAG_GA, IDI_COUNTRY_FLAG_GB, 
                    IDI_COUNTRY_FLAG_GD, IDI_COUNTRY_FLAG_GE, IDI_COUNTRY_FLAG_GG, IDI_COUNTRY_FLAG_GH, 
                    IDI_COUNTRY_FLAG_GI, IDI_COUNTRY_FLAG_GK, IDI_COUNTRY_FLAG_GL, IDI_COUNTRY_FLAG_GM, 
                    IDI_COUNTRY_FLAG_GN, IDI_COUNTRY_FLAG_GP, IDI_COUNTRY_FLAG_GQ, IDI_COUNTRY_FLAG_GR, 
                    IDI_COUNTRY_FLAG_GS, IDI_COUNTRY_FLAG_GT, IDI_COUNTRY_FLAG_GU, IDI_COUNTRY_FLAG_GW, 
                    IDI_COUNTRY_FLAG_GY, IDI_COUNTRY_FLAG_HK, IDI_COUNTRY_FLAG_HN, IDI_COUNTRY_FLAG_HR, 
                    IDI_COUNTRY_FLAG_HT, IDI_COUNTRY_FLAG_HU, IDI_COUNTRY_FLAG_ID, IDI_COUNTRY_FLAG_IE, 
                    IDI_COUNTRY_FLAG_IL, IDI_COUNTRY_FLAG_IM, IDI_COUNTRY_FLAG_IN, IDI_COUNTRY_FLAG_IO, 
                    IDI_COUNTRY_FLAG_IQ, IDI_COUNTRY_FLAG_IR, IDI_COUNTRY_FLAG_IS, IDI_COUNTRY_FLAG_IT, 
                    IDI_COUNTRY_FLAG_JE, IDI_COUNTRY_FLAG_JM, IDI_COUNTRY_FLAG_JO, IDI_COUNTRY_FLAG_JP, 
                    IDI_COUNTRY_FLAG_KE, IDI_COUNTRY_FLAG_KG, IDI_COUNTRY_FLAG_KH, IDI_COUNTRY_FLAG_KI, 
                    IDI_COUNTRY_FLAG_KM, IDI_COUNTRY_FLAG_KN, IDI_COUNTRY_FLAG_KP, IDI_COUNTRY_FLAG_KR, 
                    IDI_COUNTRY_FLAG_KW, IDI_COUNTRY_FLAG_KY, IDI_COUNTRY_FLAG_KZ, IDI_COUNTRY_FLAG_LA, 
                    IDI_COUNTRY_FLAG_LB, IDI_COUNTRY_FLAG_LC, IDI_COUNTRY_FLAG_LI, IDI_COUNTRY_FLAG_LK, 
                    IDI_COUNTRY_FLAG_LR, IDI_COUNTRY_FLAG_LS, IDI_COUNTRY_FLAG_LT, IDI_COUNTRY_FLAG_LU, 
                    IDI_COUNTRY_FLAG_LV, IDI_COUNTRY_FLAG_LY, IDI_COUNTRY_FLAG_MA, IDI_COUNTRY_FLAG_MC, 
                    IDI_COUNTRY_FLAG_MD, IDI_COUNTRY_FLAG_MG, IDI_COUNTRY_FLAG_MH, IDI_COUNTRY_FLAG_MK, 
                    IDI_COUNTRY_FLAG_ML, IDI_COUNTRY_FLAG_MM, IDI_COUNTRY_FLAG_MN, IDI_COUNTRY_FLAG_MO, 
                    IDI_COUNTRY_FLAG_MP, IDI_COUNTRY_FLAG_MQ, IDI_COUNTRY_FLAG_MR, IDI_COUNTRY_FLAG_MS, 
                    IDI_COUNTRY_FLAG_MT, IDI_COUNTRY_FLAG_MU, IDI_COUNTRY_FLAG_MV, IDI_COUNTRY_FLAG_MW, 
                    IDI_COUNTRY_FLAG_MX, IDI_COUNTRY_FLAG_MY, IDI_COUNTRY_FLAG_MZ, IDI_COUNTRY_FLAG_NA, 
                    IDI_COUNTRY_FLAG_NC, IDI_COUNTRY_FLAG_NE, IDI_COUNTRY_FLAG_NF, IDI_COUNTRY_FLAG_NG, 
                    IDI_COUNTRY_FLAG_NI, IDI_COUNTRY_FLAG_NL, IDI_COUNTRY_FLAG_NO, IDI_COUNTRY_FLAG_NP, 
                    IDI_COUNTRY_FLAG_NR, IDI_COUNTRY_FLAG_NU, IDI_COUNTRY_FLAG_NZ, IDI_COUNTRY_FLAG_OM, 
                    IDI_COUNTRY_FLAG_PA, IDI_COUNTRY_FLAG_PC, IDI_COUNTRY_FLAG_PE, IDI_COUNTRY_FLAG_PF, 
                    IDI_COUNTRY_FLAG_PG, IDI_COUNTRY_FLAG_PH, IDI_COUNTRY_FLAG_PK, IDI_COUNTRY_FLAG_PL, 
                    IDI_COUNTRY_FLAG_PM, IDI_COUNTRY_FLAG_PN, IDI_COUNTRY_FLAG_PR, IDI_COUNTRY_FLAG_PS, 
                    IDI_COUNTRY_FLAG_PT, IDI_COUNTRY_FLAG_PW, IDI_COUNTRY_FLAG_PY, IDI_COUNTRY_FLAG_QA, 
                    IDI_COUNTRY_FLAG_RO, IDI_COUNTRY_FLAG_RU, IDI_COUNTRY_FLAG_RW, IDI_COUNTRY_FLAG_SA, 
                    IDI_COUNTRY_FLAG_SB, IDI_COUNTRY_FLAG_SC, IDI_COUNTRY_FLAG_SD, IDI_COUNTRY_FLAG_SE, 
                    IDI_COUNTRY_FLAG_SG, IDI_COUNTRY_FLAG_SH, IDI_COUNTRY_FLAG_SI, IDI_COUNTRY_FLAG_SK, 
                    IDI_COUNTRY_FLAG_SL, IDI_COUNTRY_FLAG_SM, IDI_COUNTRY_FLAG_SN, IDI_COUNTRY_FLAG_SO, 
                    IDI_COUNTRY_FLAG_SR, IDI_COUNTRY_FLAG_ST, IDI_COUNTRY_FLAG_SU, IDI_COUNTRY_FLAG_SV, 
                    IDI_COUNTRY_FLAG_SY, IDI_COUNTRY_FLAG_SZ, IDI_COUNTRY_FLAG_TC, IDI_COUNTRY_FLAG_TD, 
                    IDI_COUNTRY_FLAG_TF, IDI_COUNTRY_FLAG_TG, IDI_COUNTRY_FLAG_TH, IDI_COUNTRY_FLAG_TJ, 
                    IDI_COUNTRY_FLAG_TK, IDI_COUNTRY_FLAG_TL, IDI_COUNTRY_FLAG_TM, IDI_COUNTRY_FLAG_TN, 
                    IDI_COUNTRY_FLAG_TO, IDI_COUNTRY_FLAG_TR, IDI_COUNTRY_FLAG_TT, IDI_COUNTRY_FLAG_TV, 
                    IDI_COUNTRY_FLAG_TW, IDI_COUNTRY_FLAG_TZ, IDI_COUNTRY_FLAG_UA, IDI_COUNTRY_FLAG_UG, 
                    IDI_COUNTRY_FLAG_UM, IDI_COUNTRY_FLAG_US, IDI_COUNTRY_FLAG_UY, IDI_COUNTRY_FLAG_UZ, 
                    IDI_COUNTRY_FLAG_VA, IDI_COUNTRY_FLAG_VC, IDI_COUNTRY_FLAG_VE, IDI_COUNTRY_FLAG_VG, 
                    IDI_COUNTRY_FLAG_VI, IDI_COUNTRY_FLAG_VN, IDI_COUNTRY_FLAG_VU, IDI_COUNTRY_FLAG_WF, 
                    IDI_COUNTRY_FLAG_WS, IDI_COUNTRY_FLAG_YE, IDI_COUNTRY_FLAG_YU, IDI_COUNTRY_FLAG_ZA, 
                    IDI_COUNTRY_FLAG_ZM, IDI_COUNTRY_FLAG_ZW, IDI_COUNTRY_FLAG_UK, IDI_COUNTRY_FLAG_CS,
                    IDI_COUNTRY_FLAG_EU,
            };

            CStringA countryID[] = 
            {
                    // CQ 赤道几内亚
                    // BV 布韦岛
                    // EV 萨尔瓦多
                    // GF 法属圭亚那
                    // HM 赫德与麦克唐纳群岛
                    // NU 纽埃
                    // RE 留尼汪(法属)
                    // SJ 斯瓦尔巴群岛和扬马延岛
                    // TP 东帝汶

                    ("中国"),

                    (" CZ88.NET"),      // 1
                    ("本机地址"),
                    ("局域网"),
                    ("CNNIC"),
                    ("APNIC"),          // 5
                    ("IANA"),
                    ("IANA保留地址"),
                    ("IANA保留地址6to4隧道地址"),
                    ("IANA保留地址用于网络测试"),
                    ("联合国"),         // 10
                    ("AD"),
                    ("亚太地区"),
                    ("亚太地区网络"),
                    ("非洲"),
                    ("非洲地区 "),      // 15
                    ("中非"),
                    ("北美地区"),
                    ("拉美地区"),
                    ("欧洲和中东地区"),

                    ("留尼汪"),         // 20
                    ("突尼斯"),
                    ("塞尔维亚"),
                    ("塞尔维亚和黑山"),
                    ("卢森堡"),
                    ("黑山"),           // 25
                    ("纽埃"),
                    ("安地瓜"),         // 27

                    ("美国/加拿大"),    // 28
                    ("意大利/肯尼"),
                    ("瑞士/英国"),
                    ("法属圣马丁"),
                    ("法属圭亚那"),
                    ("荷属安的列斯"),
                    ("helan"),                  // 荷兰
                    ("维多利亚"),               // 英国
                    ("奥兰群岛"),               // 芬兰

                    ("孟加拉"),                 // 孟加拉国
                    ("波斯尼亚和黑塞哥维那"),   // 波黑
                    ("阿联酋"),                 // 阿拉伯联合酋长国
                    ("英格兰"),                 // 英国
                    ("波多黎各共和国"),         // 波多黎各
                    ("罗马尼亚布"),             // 罗马尼亚
                    ("韩国，"),                 // 韩国
                    ("s246.xrea.com日本"),      // 日本
                    ("BITS国际公司欧洲IP分布"), // 欧洲
                    ("斐济"),                   // 斐济
                    ("澳大利亚｜珀斯"),

                    ("Microsoft"),
                    ("Firebrand"),
                    ("Yahoo"),
                    ("雅虎"),

                    ("雅虎中国"),
                    ("雅虎中国公司"),
                    ("IBM中国公司"),
                    ("奇虎qihoo蜘蛛"),
                    ("中经网"),
                    ("聚友网络"),
                    ("UCWEB手机浏览器"),

                    ("安道尔"),                 ("阿拉伯联合酋长国"),       ("阿富汗"),             ("安提瓜和巴布达"),
                    ("安圭拉"),                 ("阿尔巴尼亚"),             ("亚美尼亚"),           ("阿森松"),
                    ("安哥拉"),                 ("阿根廷"),                 ("萨摩亚"),             ("奥地利"),
                    ("澳大利亚"),               ("阿鲁巴"),                 ("阿塞拜疆"),           ("波黑"),
                    ("巴巴多斯"),               ("孟加拉国"),               ("比利时"),             ("布基纳法索"),
                    ("保加利亚"),               ("巴林"),                   ("布隆迪"),             ("贝宁"),
                    ("百慕大"),                 ("文莱"),                   ("玻利维亚"),           ("巴西"),
                    ("巴哈马"),                 ("不丹"),                   ("博茨瓦纳"),           ("白俄罗斯"),
                    ("伯利兹"),                 ("加拿大"),                 ("可可斯群岛"),         ("刚果(布)"),
                    ("中非共和国"),             ("刚果(金)"),               ("瑞士"),               ("科特迪瓦"), 
                    ("库克群岛"),               ("智利"),                   ("喀麦隆"),             ("中国"),
                    ("哥伦比亚"),               ("哥斯达黎加"),             ("古巴"),               ("佛得角"), 
                    ("圣诞岛"),                 ("塞浦路斯"),               ("捷克共和国"),         ("德国"),
                    ("吉布提"),                 ("丹麦"),                   ("多明哥"),             ("多米尼加"),
                    ("阿尔及利亚"),             ("厄瓜多尔"),               ("爱沙尼亚"),           ("埃及"), 
                    ("西撒哈拉"),               ("厄立特里亚"),             ("西班牙"),             ("埃塞俄比亚"),
                    ("芬兰"),                   ("斐济群岛"),               ("福克兰群岛"),         ("密克罗尼西亚联邦"),
                    ("法罗群岛"),               ("法国"),                   ("加蓬"),               ("英国"), 
                    ("格林纳达"),               ("格鲁吉亚"),               ("根西岛"),             ("加纳"),
                    ("直布罗陀"),               ("GK"),                     ("格陵兰"),             ("冈比亚"),
                    ("几内亚"),                 ("瓜德罗普"),               ("赤道几内亚"),         ("希腊"), 
                    ("南乔治亚州和南方插入岛"), ("危地马拉"),               ("关岛"),               ("几内亚比绍"),
                    ("圭亚那"),                 ("香港"),                   ("洪都拉斯"),           ("克罗地亚"),
                    ("海地"),                   ("匈牙利"),                 ("印度尼西亚"),         ("爱尔兰"), 
                    ("以色列"),                 ("马恩岛"),                 ("印度"),               ("英属印度洋领地"),
                    ("伊拉克"),                 ("伊朗"),                   ("冰岛"),               ("意大利"),
                    ("泽西岛"),                 ("牙买加"),                 ("约旦"),               ("日本"),
                    ("肯尼亚"),                 ("吉尔吉斯斯坦"),           ("柬埔寨"),             ("基里巴斯"),
                    ("科摩洛"),                 ("圣基茨和尼维斯"),         ("朝鲜"),               ("韩国"),
                    ("科威特"),                 ("开曼群岛"),               ("哈萨克斯坦"),         ("老挝"), 
                    ("黎巴嫩"),                 ("圣卢西亚"),               ("列支敦士登"),         ("斯里兰卡"),
                    ("利比里亚"),               ("莱索托"),                 ("立陶宛"),             ("立陶宛"),
                    ("拉脱维亚"),               ("利比亚"),                 ("摩洛哥"),             ("摩纳哥"), 
                    ("摩尔多瓦"),               ("马达加斯加"),             ("马绍尔群岛"),         ("马其顿"),
                    ("马里"),                   ("缅甸"),                   ("蒙古"),               ("澳门"),
                    ("北马里亚纳群岛"),         ("马提尼克岛"),             ("毛里塔尼亚"),         ("蒙塞拉特岛"),
                    ("马耳他"),                 ("毛里求斯"),               ("马尔代夫"),           ("马拉维"),
                    ("墨西哥"),                 ("马来西亚"),               ("莫桑比克"),           ("纳米比亚"),
                    ("新喀里多尼亚"),           ("尼日尔"),                 ("诺福克岛"),           ("尼日利亚"),
                    ("尼加拉瓜"),               ("荷兰"),                   ("挪威"),               ("尼泊尔"),
                    ("瑙鲁"),                   ("纽鄂岛"),                 ("新西兰"),             ("阿曼"),
                    ("巴拿马"),                 ("法属波利尼西亚"),         ("秘鲁"),               ("法属玻里尼西亚"),
                    ("巴布亚新几内亚"),         ("菲律宾"),                 ("巴基斯坦"),           ("波兰"),
                    ("圣皮埃尔和密克隆"),       ("皮特凯恩岛"),             ("波多黎各"),           ("巴勒斯坦"),
                    ("葡萄牙"),                 ("帕劳"),                   ("巴拉圭"),             ("卡塔尔"), 
                    ("罗马尼亚"),               ("俄罗斯"),                 ("卢旺达"),             ("沙特阿拉伯"),
                    ("所罗门群岛"),             ("塞舌尔"),                 ("苏丹"),               ("瑞典"),
                    ("新加坡"),                 ("圣海伦娜"),               ("斯洛文尼亚"),         ("斯洛伐克"),
                    ("塞拉利昂"),               ("圣马力诺"),               ("塞内加尔"),           ("索马里"),
                    ("苏里南"),                 ("圣多美和普林西比"),       ("苏联"),               ("萨尔瓦多"),
                    ("叙利亚"),                 ("斯威士兰"),               ("特克斯和凯科斯群岛"), ("乍得"),
                    ("法属南方领土"),           ("多哥"),                   ("泰国"),               ("塔吉克斯坦"),
                    ("托克劳"),                 ("东帝汶"),                 ("土库曼斯坦"),         ("北非"),
                    ("汤加"),                   ("土耳其"),                 ("特立尼达和多巴哥"),   ("图瓦卢"),
                    ("台湾省"),                 ("坦桑尼亚"),               ("乌克兰"),             ("乌干达"),
                    ("美国辅修在外的岛"),       ("美国"),                   ("乌拉圭"),             ("乌兹别克斯坦"),
                    ("梵蒂冈"),                 ("圣文森特和格林纳丁斯"),   ("委内瑞拉"),           ("英属维尔京群岛"), 
                    ("美属维尔京群岛"),         ("越南"),                   ("瓦努阿图"),           ("瓦利斯和富图纳"),
                    ("美属萨摩亚"),             ("也门"),                   ("南斯拉夫"),           ("南非"),
                    ("赞比亚"),                 ("津巴布韦"),               ("英国"),               ("捷克"), 
                    ("欧洲")
            };

            int nCount = sizeof(resID) / sizeof(WORD);

            if (NULL != m_pCountry)
            {
                delete[] m_pCountry;
            }

            m_pCountry = new COUNTRY[nCount];

            if (NULL != m_pCountry)
            {
                for (int i = 0; i < nCount; i++)
                {
                    m_pCountry[i].nBegin = m_strCountry.GetLength();
                    m_pCountry[i].byCount = countryID[i].GetLength();
                    m_pCountry[i].shFlagIndex = i;

                    m_strCountry += countryID[i];

                    m_CountryMap.SetAt(countryID[i], &m_pCountry[i]);

                    iconHandle = LoadIcon(hFlagDll, MAKEINTRESOURCE(resID[i]));
                    if (NULL == iconHandle)
                    {
                        TRACE(_T("Invalid resID, maybe you need to upgrade your flag icon Dll, resId = %d\n"), resID[i]);
                    }

                    m_CountryFlagImageList.Add(iconHandle);
                }

                FreeLibrary(hFlagDll);
                return true;
            }
        }

        FreeLibrary(hFlagDll);
    }
    catch(...)
    {
        
        TRACE(_T("CXTIP2Country::LoadCountryFlagLib Error:%d\n"), ::GetLastError());
        m_CountryFlagImageList.DeleteImageList();
    }
    
    return false;
}

// 加载纯真IP库
bool CXTIP2Country::LoadFromFile()
{
    CFile file;
    if (file.Open(g_ProFile.m_strCurPath + _T("\\res\\eMule\\QQWry.Dat"), CFile::modeRead))
    {
        m_IpRangeMap.RemoveAll();

        ULONGLONG ullFileLen = file.GetLength();

        if (NULL != m_pszFile) delete[] m_pszFile;

        #pragma warning(disable : 4244)
        m_pszFile = new char[ullFileLen];
        #pragma warning(default : 4244)

        if (NULL != m_pszFile)
        {
            #pragma warning(disable : 4244)
            UINT nReadLen = file.Read(m_pszFile, ullFileLen);
            #pragma warning(default : 4244)
            file.Close();

            if (nReadLen == ullFileLen)
            {
                DWORD dwBeginIndex = 0;
                DWORD dwEndIndex   = 0;
                DWORD dwBeginIP    = 0;
                DWORD dwEndIP      = 0;
                DWORD dwOffset     = 0;
                DWORD dwAddrOffset = 0;
                DWORD dwProgress[3] = {0};
                CString strCountry;

                // 文件结构
                // | 开始索引位置(4) | 结束索引位置(4) | 一条数据:开始IP(4),结束IP的地址(3) | 数据(有一定的结构,见switch结构) |

                memcpy(&dwBeginIndex, &m_pszFile[0], 4);    // 开始索引位置
                memcpy(&dwEndIndex,   &m_pszFile[4], 4);    // 结束索引位置

                dwProgress[0] = (dwEndIndex - dwBeginIndex) / 50;   // 确定每一块的索引数
                int nCount = (dwEndIndex  - dwBeginIndex) / 7 + 1;  // 记录个数

                if (NULL != m_pRange) delete[] m_pRange;
                m_pRange = new IPRANG[nCount];

                if (NULL == m_pRange) return false;

                for (DWORD i = dwBeginIndex; i <= dwEndIndex; i += 7)
                {
                    // 计算进度
                    dwProgress[1] = (i - dwBeginIndex) / dwProgress[0];
                    if (dwProgress[1] != dwProgress[2])
                    {
                        dwProgress[2] = dwProgress[1];
                        ::SendMessage(m_hWnd, WM_IP2COUNTRY_NOTIFY, dwProgress[2], NULL);   // 向窗体发送进度消息
                    }

                    memcpy(&dwBeginIP, &m_pszFile[i], 4);       // 开始IP
                    memcpy(&dwOffset, &m_pszFile[i+4], 3);      // 结构体地址
                    memcpy(&dwEndIP, &m_pszFile[dwOffset], 4);  // 结构体数

                    switch(m_pszFile[dwOffset + 4])
                    {
                    case 1:
                        {
                            memcpy(&dwOffset, &m_pszFile[dwOffset + 4 + 1], 3);
                            switch (m_pszFile[dwOffset])
                            {
                            case 2:
                                {
                                    DWORD dwNewOffset = 0;
                                    memcpy(&dwNewOffset, &m_pszFile[dwOffset + 1], 3);
                                    strCountry = &m_pszFile[dwNewOffset];

                                    if (dwNewOffset != 0)
                                    {
                                        dwOffset += 1 + 3;
                                        if (m_pszFile[dwOffset] != 1 && m_pszFile[dwOffset] != 2)
                                        {
                                            /*
                                            IP(4字节)
                                            0x01(1字节)
                                            Offset(3字节) --> 0x02(1字节)
                                            ----------------  Offset(3字节) --> 国家(\0结束)
                                            ----------------  城市(\0结束)
                                            */

                                            dwAddrOffset = dwOffset;
                                        }
                                        else
                                        {
                                            /*
                                            IP(4字节)
                                            0x01(1字节)
                                            Offset(3字节) --> 0x02(1字节)
                                            ----------------  Offset(3字节) --> 国家(\0结束)
                                            ----------------  0x01或0x02(1字节)
                                            ----------------  Offset(3字节) --> 城市(\0结束)
                                            */
                                            memcpy(&dwAddrOffset, &m_pszFile[dwOffset + 1], 3);
                                        }
                                    }
                                    break;
                                }
                            default:
                                {
                                    strCountry = &m_pszFile[dwOffset];
                                    dwOffset = dwOffset + strCountry.GetLength() + 1;

                                    if (m_pszFile[dwOffset] != 2)
                                    {
                                        /*
                                        IP(4字节)
                                        0x01(1字节)
                                        国家(\0结束)
                                        城市(\0结束)
                                        */

                                        dwAddrOffset = dwOffset;
                                    }
                                    else
                                    {
                                        /*
                                        IP(4字节)
                                        0x01(1字节)
                                        国家(\0结束)
                                        0x02(1字节)
                                        Offset(3字节) --> 城市(\0结束)
                                        */
                                        memcpy(&dwAddrOffset, &m_pszFile[dwOffset + 1], 3);
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    case 2:
                        {
                            /*
                            IP(4字节)
                            0x02(1字节)
                            Offset(3字节) --> 国家(\0结束)
                            城市(\0结束)
                            */

                            DWORD dwNewOffset = dwOffset;
                            memcpy(&dwOffset, &m_pszFile[dwOffset + 4 + 1], 3);
                            strCountry = &m_pszFile[dwOffset];
                            dwOffset = dwNewOffset + 4 + 1 + 3;

                            if (m_pszFile[dwOffset] != 2)
                            {
                                /*
                                IP(4字节)
                                0x02(1字节)
                                Offset(3字节) --> 国家(\0结束)
                                城市(\0结束)
                                */
                                dwAddrOffset = dwOffset;
                            }
                            else
                            {
                                /*
                                IP(4字节)
                                0x02(1字节)
                                Offset(3字节) --> 国家(\0结束)
                                0x02(1字节)
                                Offset(3字节) --> 城市(\0结束)
                                */
                                memcpy(&dwAddrOffset, &m_pszFile[dwOffset + 1], 3);
                            }
                            break;
                        }
                    default:
                        {
                            strCountry = &m_pszFile[dwOffset+4];
                            dwOffset = dwOffset + 4 + strCountry.GetLength() + 1;

                            if (m_pszFile[dwOffset] != 2)
                            {
                                /*
                                IP(4字节)
                                国家(\0结束)
                                城市(\0结束)
                                */
                                dwAddrOffset = dwOffset;
                            }
                            else
                            {
                                /*
                                IP(4字节)
                                国家(\0结束)
                                0x02(1字节)
                                Offset(3字节) --> 城市(\0结束)
                                */
                                memcpy(&dwAddrOffset, &m_pszFile[dwOffset + 1], 3);
                            }
                            break;
                        }
                    }

                    AddIPRange(dwBeginIP, dwEndIP, strCountry, dwAddrOffset);
                    dwAddrOffset = 0;
                }
            }

            //------------------------------------------------------------
            // 执行成功就不需要了

            m_CountryMap.RemoveAll();

            ::SendMessage(m_hWnd, WM_IP2COUNTRY_NOTIFY, 100, NULL);
            return true;
        }
        else
        {
            file.Close();
        }       
    }
    else
    {
        TRACE(_T("Open QQWry.Dat Error %d\n"), ::GetLastError());
    }

    return false;
}

bool CXTIP2Country::AddIPRange(DWORD dwIpFrom, DWORD dwIpTo,
                               CString &strCountryName,
                               DWORD dwCityOffset)
{
    if (NULL != m_pRange)
    {
        COUNTRY* pCountry = NULL;
        int nIndex = (int)m_IpRangeMap.GetCount();

        if (!m_CountryMap.Lookup(strCountryName, pCountry))
        {
            if (-1 != m_strProvince.Find(strCountryName.Left(4)))
            {
                pCountry = &m_pCountry[DEFAULT_COUNTRY]; // 默认是中国
            }
            else
            {
                pCountry = &m_pCountry[NOFLAG_COUNTRY];
                TRACE(_T("%s\n"), strCountryName);
            }
        }

        m_pRange[nIndex].dwIpStart = dwIpFrom;
        m_pRange[nIndex].dwIpEnd = dwIpTo;
        m_pRange[nIndex].dwCityOffset = dwCityOffset;
        m_pRange[nIndex].pCountry = pCountry;
        m_IpRangeMap.SetAt(dwIpFrom, &m_pRange[nIndex]);
        return true;
    }
    else
    {
        return false;
    }
}

// ClientIP     IN
// uCountryFlag OUT
// strAddr      OUT
void CXTIP2Country::GetCountryFromIP(DWORD dwIP, WORD &wFlag, CString &strAddr)
{
    if ((0 == dwIP) || (m_IpRangeMap.IsEmpty()))
    {
        wFlag = NOFLAG_COUNTRY;
        strAddr = _T("");
        return;
    }

    const CRBMap<DWORD, IPRANG*>::CPair* pair = NULL;
    IPRANG *pIPRang = NULL;

    POSITION pos = m_IpRangeMap.FindFirstKeyAfter(dwIP);

    while(NULL != pos)
    {
        pair = m_IpRangeMap.GetPrev(pos);
        if (NULL != pair)
        {
            pIPRang = pair->m_value;

            if (dwIP >= pIPRang->dwIpStart && dwIP <= pIPRang->dwIpEnd)
            {
                wFlag = pIPRang->pCountry->shFlagIndex;
                strAddr = m_strCountry.Mid(pIPRang->pCountry->nBegin, pIPRang->pCountry->byCount);

                if ((0 != pIPRang->dwCityOffset) 
                    && (0 != strcmp(&m_pszFile[pIPRang->dwCityOffset], " CZ88.NET")))
                {
                    strAddr += &m_pszFile[pIPRang->dwCityOffset];
                }
                return;
            }
        }
        else
        {
            break;
        }
    }

    wFlag = NOFLAG_COUNTRY;
    strAddr = _T("");
    return; 
}


