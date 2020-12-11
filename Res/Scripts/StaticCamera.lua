camera = {}

function Start()
	camera = GetComponent(this, ComponentType.CAMERA);
end

function Update(deltaTime)
	if(GetKeyDown(Input.KEY_2)) then
		SetMainCamera(camera)
	end
end