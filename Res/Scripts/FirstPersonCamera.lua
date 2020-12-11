camera = {}

function Start()
	camera = GetComponent(this, ComponentType.CAMERA);
	SetMainCamera(camera)
end

function Update(deltaTime)
	if(GetKeyDown(Input.KEY_1)) then
		SetMainCamera(camera)
	end
end