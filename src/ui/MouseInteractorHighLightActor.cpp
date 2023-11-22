#pragma once

#include "ui/MouseInteractorHighLightActor.h"

#include <vtkNamedColors.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkObjectFactory.h>

namespace ui {
// Handle mouse events

vtkStandardNewMacro(MouseInteractorHighLightActor);

MouseInteractorHighLightActor::MouseInteractorHighLightActor()
{
    LastPickedActor    = NULL;
    LastPickedProperty = vtkProperty::New();
}
MouseInteractorHighLightActor::~MouseInteractorHighLightActor()
{
    LastPickedProperty->Delete();
}

void MouseInteractorHighLightActor::OnLeftButtonDown()
{
    vtkNew<vtkNamedColors> colors;

    int* clickPos = this->GetInteractor()->GetEventPosition();

    // Pick from this location.
    vtkNew<vtkPropPicker> picker;
    picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

    // If we picked something before, reset its property.
    if (this->LastPickedActor)
    {
        this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);
    }
    this->LastPickedActor = picker->GetActor();
    if (this->LastPickedActor)
    {
        // Save the property of the picked actor so that we can
        // restore it next time.
        this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());
        // Highlight the picked actor by changing its properties.
        this->LastPickedActor->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
        this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
        this->LastPickedActor->GetProperty()->SetSpecular(0.0);
        this->LastPickedActor->GetProperty()->EdgeVisibilityOn();
    }

    // Forward events.
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void MouseInteractorHighLightActor::getSelectedActor(vtkSmartPointer<vtkActor>& actor)
{
    actor = LastPickedActor;
}

} // namespace ui