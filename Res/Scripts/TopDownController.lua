camera = {}

cMoveSpeed = 10
cBoostScale = 4
cRotSpeed = 1.25

function Move(Position, Rotation, isForward, deltaTime, isBoosted)
	scalar = 0;

	if(isForward) then scalar = 1
	else scalar = -1 end

	if(isBoosted) then 
		scalar = scalar * cBoostScale
	end

	Position.x = Position.x + scalar * math.cos(Rotation.y) * cMoveSpeed * deltaTime
	Position.z = Position.z - scalar * math.sin(Rotation.y) * cMoveSpeed * deltaTime
end

function Start()
	camera = GetComponent(this, ComponentType.CAMERA);
end

function Update(deltaTime)
	if(GetKeyDown(Input.KEY_3)) then
		SetMainCamera(camera)
	end

	if(GetMainCamera() == camera) then
		Position = parent:GetParent():GetTransform().Position
		Rotation = parent:GetParent():GetTransform().Rotation

		isBoosted = GetKey(Input.KEY_SHIFT)

		if(GetKey(Input.KEY_W)) then
			Move(Position, Rotation, true, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_S)) then
			Move(Position, Rotation, false, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_A)) then
			Rotation.y = Rotation.y - cRotSpeed * deltaTime
		end

		if(GetKey(Input.KEY_D)) then
			Rotation.y = Rotation.y + cRotSpeed * deltaTime
		end
	end
end