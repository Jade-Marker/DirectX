initialPos = {}
currTime = 0

function Start()
	initialPos = InitialTransform.Position
	Log("Lua start")
end

function Update(deltaTime)
	currTime =  currTime + deltaTime
	Transform.Position.y = initialPos.y + 5 * math.sin(currTime)
end