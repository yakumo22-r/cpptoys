# ykm_app lib

## app (Mother module)

### include:
- system api
- ykm_app

### options:
- script-engine
- script-bind
- viewbox
- socket
- messege system
- voice system

## graphic (with app)
> render hardware interface

### include:
- graphic api
- vulkan wrap

### options:
- script-bind (need script)
- opengl wrap (only windows)
- dx11 wrap (only windows)
- dx12 wrap (only windows)
- metal wrap (only apple)
- shader compiler

## network (with app)

### require:
- socket

### options:
- script-bind (need script)

## view (mini Mother module) (with app)

### require:
- graphic

### include:
- graphic resources manager
- view system manager
- font-sys
- app-ui
- view-entry

### options:
- 2d-view
- vector-img
- particles
- physiscs

## view3d (with view)

