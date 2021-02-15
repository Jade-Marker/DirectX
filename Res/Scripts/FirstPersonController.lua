camera = {}
initialPos = {}

cMoveSpeed = 10
cBoostScale = 4
cRotSpeed = 0.001
cCrouchAmount = 3

EulerRotation = {}

function Move(Position, EulerRotation, isForward, deltaTime, isBoosted)
	scalar = 0;

	if(isForward) then scalar = 1
	else scalar = -1 end

	if(isBoosted) then 
		scalar = scalar * cBoostScale
	end

	Position.x = Position.x - scalar * math.cos(EulerRotation.y + math.pi/2) * cMoveSpeed * deltaTime
	Position.z = Position.z + scalar * math.sin(EulerRotation.y + math.pi/2) * cMoveSpeed * deltaTime
end

function MoveSide(Position, EulerRotation, isLeft, deltaTime, isBoosted)
	scalar = 0;

	if(isLeft) then scalar = 1
	else scalar = -1 end

	if(isBoosted) then 
		scalar = scalar * cBoostScale
	end

	Position.x = Position.x - scalar * math.cos(EulerRotation.y) * cMoveSpeed * deltaTime
	Position.z = Position.z + scalar * math.sin(EulerRotation.y) * cMoveSpeed * deltaTime
end

function Start()
	camera = GetComponent(this, ComponentType.CAMERA);
	initialPos = InitialTransform.Position

	EulerRotation = Vector3D(0,0,0)
end

function Update(deltaTime)
	if(GetKeyDown(Input.KEY_5)) then
		SetMainCamera(camera)
	end

	if(GetMainCamera() == camera) then
		Position = Transform.Position
		deltaX, deltaY = GetDeltaMousePos()
		isBoosted = GetKey(Input.KEY_SHIFT)

		EulerRotation = EulerRotation + Vector3D(deltaY * cRotSpeed, deltaX * cRotSpeed, 0)
		Transform.Rotation = Quaternion.EulerToQuaternion(EulerRotation.x, EulerRotation.y, EulerRotation.z)

		if(GetKey(Input.KEY_W)) then
			Move(Position, EulerRotation, true, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_S)) then
			Move(Position, EulerRotation, false, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_A)) then
			MoveSide(Position, EulerRotation, true, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_D)) then
			MoveSide(Position, EulerRotation, false, deltaTime, isBoosted)
		end

		if(GetKey(Input.KEY_CONTROL)) then
			Position.y = initialPos.y - cCrouchAmount
		else
			Position.y = initialPos.y	
		end
	end
end