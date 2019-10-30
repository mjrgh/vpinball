#include "stdafx.h"
#include "Properties/RampVisualsProperty.h"
#include <WindowsX.h>

RampVisualsProperty::RampVisualsProperty(VectorProtected<ISelect> *pvsel) : BaseProperty(IDD_PROPRAMP_VISUALS, pvsel)
{
    m_typeList.push_back("RampTypeFlat");
    m_typeList.push_back("RampType4Wire");
    m_typeList.push_back("RampType2Wire");
    m_typeList.push_back("RampType3WireLeft");
    m_typeList.push_back("RampType3WireRight");
    m_typeList.push_back("RampType1Wire");

    m_imageModeList.push_back("ImageModeWorld");
    m_imageModeList.push_back("ImageModeWrap");
}

void RampVisualsProperty::UpdateVisuals()
{
    for (int i = 0; i < m_pvsel->Size(); i++)
    {
        if ((m_pvsel->ElementAt(i) == NULL) || (m_pvsel->ElementAt(i)->GetItemType() != eItemRamp))
            continue;
        Ramp *ramp = (Ramp *)m_pvsel->ElementAt(i);
        PropertyDialog::UpdateComboBox(m_typeList, m_typeCombo, m_typeList[(int)ramp->m_d.m_type - 1].c_str());
        PropertyDialog::UpdateTextureComboBox(ramp->GetPTable()->GetImageList(), m_imageCombo, ramp->m_d.m_szImage);
        PropertyDialog::UpdateMaterialComboBox(ramp->GetPTable()->GetMaterialList(), m_materialCombo, ramp->m_d.m_szMaterial);
        PropertyDialog::UpdateComboBox(m_imageModeList, m_modeCombo, m_imageModeList[(int)ramp->m_d.m_imagealignment - 1].c_str());
        PropertyDialog::SetFloatTextbox(m_depthBiasEdit, ramp->m_d.m_depthBias);
        PropertyDialog::SetFloatTextbox(m_topHeightEdit, ramp->m_d.m_heighttop);
        PropertyDialog::SetFloatTextbox(m_bottomHeightEdit, ramp->m_d.m_heightbottom);
        PropertyDialog::SetFloatTextbox(m_topWidthEdit, ramp->m_d.m_widthtop);
        PropertyDialog::SetFloatTextbox(m_bottomWdthEdit, ramp->m_d.m_widthbottom);
        PropertyDialog::SetFloatTextbox(m_leftWallEdit, ramp->m_d.m_leftwallheightvisible);
        PropertyDialog::SetFloatTextbox(m_rightWallEdit, ramp->m_d.m_rightwallheightvisible);
        PropertyDialog::SetFloatTextbox(m_diameterEdit, ramp->m_d.m_wireDiameter);
        PropertyDialog::SetFloatTextbox(m_distanceXEdit, ramp->m_d.m_wireDistanceX);
        PropertyDialog::SetFloatTextbox(m_distanceYEdit, ramp->m_d.m_wireDistanceY);
        PropertyDialog::SetCheckboxState(::GetDlgItem(GetHwnd(), 9), ramp->m_d.m_imageWalls);
        PropertyDialog::SetCheckboxState(::GetDlgItem(GetHwnd(), 112), ramp->m_d.m_visible);
        PropertyDialog::SetCheckboxState(::GetDlgItem(GetHwnd(), IDC_RAMP_REFLECT_ENABLED_CHECK), ramp->m_d.m_reflectionEnabled);
    }
}

void RampVisualsProperty::UpdateProperties(const int dispid)
{
    for (int i = 0; i < m_pvsel->Size(); i++)
    {
        if ((m_pvsel->ElementAt(i) == NULL) || (m_pvsel->ElementAt(i)->GetItemType() != eItemRamp))
            continue;
        Ramp *ramp = (Ramp *)m_pvsel->ElementAt(i);
        switch (dispid)
        {
            case 1:
                ramp->m_d.m_heightbottom = PropertyDialog::GetFloatTextbox(m_bottomHeightEdit);
                break;
            case 2:
                ramp->m_d.m_heighttop = PropertyDialog::GetFloatTextbox(m_topHeightEdit);
                break;
            case 3:
                ramp->m_d.m_widthbottom = PropertyDialog::GetFloatTextbox(m_bottomWdthEdit);
                break;
            case 4:
                ramp->m_d.m_widthtop = PropertyDialog::GetFloatTextbox(m_topWidthEdit);
                break;
            case 6:
                ramp->m_d.m_type = (RampType)(PropertyDialog::GetComboBoxIndex(m_typeCombo, m_typeList) + 1);
                break;
            case 8:
                ramp->m_d.m_imagealignment = (RampImageAlignment)(PropertyDialog::GetComboBoxIndex(m_modeCombo, m_imageModeList) + 1);
                break;
            case 9:
                ramp->m_d.m_imageWalls = PropertyDialog::GetCheckboxState(::GetDlgItem(GetHwnd(), 9));
                break;
            case 108:
                ramp->m_d.m_leftwallheightvisible = PropertyDialog::GetFloatTextbox(m_leftWallEdit);
                break;
            case 109:
                ramp->m_d.m_rightwallheightvisible = PropertyDialog::GetFloatTextbox(m_rightWallEdit);
                break;
            case 112:
                ramp->m_d.m_visible = PropertyDialog::GetCheckboxState(::GetDlgItem(GetHwnd(), 112));
                break;
            case IDC_RAMP_REFLECT_ENABLED_CHECK:
                ramp->m_d.m_reflectionEnabled = PropertyDialog::GetCheckboxState(::GetDlgItem(GetHwnd(), IDC_RAMP_REFLECT_ENABLED_CHECK));
                break;
            case IDC_DEPTH_BIAS:
                ramp->m_d.m_depthBias = PropertyDialog::GetFloatTextbox(m_depthBiasEdit);
                break;
            case IDC_WIRE_DIAMETER:
                ramp->m_d.m_wireDiameter = PropertyDialog::GetFloatTextbox(m_diameterEdit);
                break;
            case IDC_WIRE_DISTX:
                ramp->m_d.m_wireDistanceX = PropertyDialog::GetFloatTextbox(m_distanceXEdit);
                break;
            case IDC_WIRE_DISTY:
                ramp->m_d.m_wireDistanceY = PropertyDialog::GetFloatTextbox(m_distanceYEdit);
                break;
            default:
                break;
        }
    }
    UpdateVisuals();
}

BOOL RampVisualsProperty::OnInitDialog()
{
    AttachItem(6, m_typeCombo);
    AttachItem(1500, m_imageCombo);
    AttachItem(IDC_MATERIAL_COMBO, m_materialCombo);
    AttachItem(8, m_modeCombo);
    AttachItem(IDC_DEPTH_BIAS, m_depthBiasEdit);
    AttachItem(2, m_topHeightEdit);
    AttachItem(1, m_bottomHeightEdit);
    AttachItem(4, m_topWidthEdit);
    AttachItem(3, m_bottomWdthEdit);
    AttachItem(108, m_leftWallEdit);
    AttachItem(109, m_rightWallEdit);
    AttachItem(IDC_WIRE_DIAMETER, m_diameterEdit);
    AttachItem(IDC_WIRE_DISTX, m_distanceXEdit);
    AttachItem(IDC_WIRE_DISTY, m_distanceYEdit);
    UpdateVisuals();
    return TRUE;
}

BOOL RampVisualsProperty::OnCommand(WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    const int dispID = LOWORD(wParam);

    switch (HIWORD(wParam))
    {
        case EN_KILLFOCUS:
        case CBN_KILLFOCUS:
        {
            UpdateProperties(dispID);
            return TRUE;
        }
        case BN_CLICKED:
        {
            UpdateProperties(dispID);
            return TRUE;
        }
    }
    return FALSE;
}

