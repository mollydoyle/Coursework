function varargout = birdIdentifier(varargin)
% BIRDIDENTIFIER MATLAB code for birdIdentifier.fig
%      BIRDIDENTIFIER, by itself, creates a new BIRDIDENTIFIER or raises the existing
%      singleton*.
%
%      H = BIRDIDENTIFIER returns the handle to a new BIRDIDENTIFIER or the handle to
%      the existing singleton*.
%
%      BIRDIDENTIFIER('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in BIRDIDENTIFIER.M with the given input arguments.
%
%      BIRDIDENTIFIER('Property','Value',...) creates a new BIRDIDENTIFIER or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before birdIdentifier_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to birdIdentifier_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help birdIdentifier

% Last Modified by GUIDE v2.5 10-Apr-2019 19:07:41

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @birdIdentifier_OpeningFcn, ...
                   'gui_OutputFcn',  @birdIdentifier_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before birdIdentifier is made visible.
function birdIdentifier_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to birdIdentifier (see VARARGIN)

% Choose default command line output for birdIdentifier
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes birdIdentifier wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = birdIdentifier_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function questionText_Callback(hObject, eventdata, handles)
% hObject    handle to questionText (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of questionText as text
%        str2double(get(hObject,'String')) returns contents of questionText as a double


% --- Executes during object creation, after setting all properties.
function questionText_CreateFcn(hObject, eventdata, handles)
% hObject    handle to questionText (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in yesPushbutton.
function yesPushbutton_Callback(hObject, eventdata, handles)
% hObject    handle to yesPushbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
total = str2double(get(handles.counterText,'String'));
total = total + 1
set(handles.counterText,'String',num2str(total));
handles.questionText.Value=1;
BirdCompleteProgramF(handles)
% --- Executes on button press in noPushbutton2.
function noPushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to noPushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
total = str2double(get(handles.counterText,'String'));
total = total + 1
set(handles.counterText,'String',num2str(total));
handles.questionText.Value=0;
BirdCompleteProgramF(handles)

function counterText_Callback(hObject, eventdata, handles)
% hObject    handle to counterText (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of counterText as text
%        str2double(get(hObject,'String')) returns contents of counterText as a double


% --- Executes during object creation, after setting all properties.
function counterText_CreateFcn(hObject, eventdata, handles)
% hObject    handle to counterText (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
