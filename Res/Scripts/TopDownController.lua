camera = {}

cMoveSpeed = 10
cBoostScale = 4
cRotSpeed = 1.25

function Move(EulerRotation, isForward, deltaTime, isBoosted)
	scalar = 0;

	if(isForward) then scalar = 1
	else scalar = -1 end

	if(isBoosted) then 
		scalar = scalar * cBoostScale
	end

	scalar = scalar * cMoveSpeed * deltaTime

	sinAngle = math.sin(EulerRotation.y)
	cosAngle = math.cos(EulerRotation.y)
	parent:GetParent():GetTransform():Translate(Vector3D(scalar * cosAngle,0,scalar * sinAngle))
end

function Start()
	camera = GetComponent(this, ComponentType.CAMERA);
end

function Update(deltaTime)
	if(GetKeyDown(Input.KEY_3)) then
		SetMainCamera(camera)
	end

	if(GetMainCamera() == camera) then
		EulerRotation = parent:GetParent():GetTransform().Rotation:ToEuler()

		isBoosted = GetKey(Input.KEY_SHIFT)

		if(GetKey(Input.KEY_W)) then
			Move(EulerRotation, true, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_S)) then
			Move(EulerRotation, false, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_A)) then
			parent:GetParent():GetTransform():Rotate(Vector3D(0, -cRotSpeed * deltaTime, 0))
		end

		if(GetKey(Input.KEY_D)) then
			parent:GetParent():GetTransform():Rotate(Vector3D(0, cRotSpeed * deltaTime, 0))
		end
	end
end