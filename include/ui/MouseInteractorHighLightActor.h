#pragma once

#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkObjectFactory.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>

namespace ui {
// Handle mouse events
class MouseInteractorHighLightActor : public vtkInteractorStyleTrackballCamera
{
  public:
    static MouseInteractorHighLightActor* New();
    vtkTypeMacro(MouseInteractorHighLightActor, vtkInteractorStyleTrackballCamera);

    MouseInteractorHighLightActor();
    virtual ~MouseInteractorHighLightActor();
    virtual void OnLeftButtonDown() override;

  private:
    vtkActor* LastPickedActor;
    vtkProperty* LastPickedProperty;
};

} // namespace ui